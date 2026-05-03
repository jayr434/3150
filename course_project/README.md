# BGP Simulator

A C++ BGP (Border Gateway Protocol) simulator that models announcement propagation across the internet's AS (Autonomous System) topology, with ROV (Route Origin Validation) support.

This is a BGP simulator for CSE 3150. It models announcement propagation through AS system topology, as well as implementing ROV support. 


Requirements:
- C++17
- Build with make (and make clean)

# Usage

```
./bgp_sim <topology_file> <announcements.csv> <rov_asns.csv> <output.csv>
```

- topology_file — CAIDA AS file, `provider_asn|customer_asn|-1|source` 
- announcements.csv — Seed announcements with header `seed_asn,prefix,rov_invalid`. The `rov_invalid` field is `True` or `False`.
- rov_asns.csv — One ASN per line 
- output.csv — Output file


## Testing

```bash
./run_tests                    # unit tests (graph, cycle detection, parsing)
./run_tests <caida_file.txt>   # + integration test against real CAIDA data
```

To verify against the provided test scenarios:

```bash
./bgp_sim prefix/CAIDAASGraphCollector_2025.10.15.txt prefix/anns.csv prefix/rov_asns.csv /tmp/out.csv
./compare_output.sh prefix/ribs.csv /tmp/out.csv
```

# Design
## AS Graph

Each AS is stored in an `unordered_map<uint32_t, AS>` keyed by ASN. The AS as a struct holds three vectors of ASNs for:
- providers
- customers
- peers
 I store ASNs rather than pointers. The map is set to 100k size since the real dataset has ~79k ASes.

### Cycle Detection and Flattening

Both use Kahn's algorithm (topological sort via BFS). In-degree = number of customers. ASes with zero customers get rank 0, then their providers get rank 1, etc. This is iterative (no stack overflow on deep chains) and dual-purpose — if not all ASes get processed, a cycle exists, and otherwise we get the propagation ranks out of it directly.

The result is a `vector<vector<uint32_t>>` where index = rank.

### Policy Classes

```
Policy (base)
  └── BGPPolicy 
        └── ROVPolicy (drops rov_invalid on receive)
```

Each AS holds a `unique_ptr<Policy>`. Default is BGPPolicy, ROV ASes get swapped to ROVPolicy after reading the ROV file. The local RIB and received queue live in the base class.

### Propagation

Three phases, which implicitly enforce valley-free routing:

1. Up (rank 0 to max) — process queue, then send local RIB to providers (tagged as from-customer)
2. Across (peers, one hop) — all ASes send to peers, then all process. Two passes prevents multi-hop.
3. Down (max to 0) — send to customers, then next rank down processes (tagged as from-provider)

Customer-learned routes go everywhere. Peer-learned only go down. Provider-learned only go down.

### Conflict Resolution

When an AS gets multiple announcements for the same prefix:

1. Best relationship (Origin > Customer > Peer > Provider)
2. Shortest AS path
3. Lowest next-hop ASN

### ROV

ROVPolicy overrides `receive()` — drops any announcement with rov_invalid=true before it enters the queue. The flag is preserved through propagation so downstream ROV ASes still catch it.


Note:

All readers strip `\r` for Windows line endings. Topology parser uses `string::find` for pipe delimiting.
