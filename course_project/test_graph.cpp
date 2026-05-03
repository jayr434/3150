#include "as_graph.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// ── minimal test harness ──────────────────────────────────────────────────────

static int passed = 0;
static int failed = 0;

static void check(const std::string& name, bool condition) {
    if (condition) {
        std::cout << "[PASS] " << name << "\n";
        ++passed;
    } else {
        std::cout << "[FAIL] " << name << "\n";
        ++failed;
    }
}

// ── helpers ───────────────────────────────────────────────────────────────────

static bool hasProvider(const AS& as, uint32_t asn) {
    return std::find(as.providers.begin(), as.providers.end(), asn) != as.providers.end();
}
static bool hasCustomer(const AS& as, uint32_t asn) {
    return std::find(as.customers.begin(), as.customers.end(), asn) != as.customers.end();
}
static bool hasPeer(const AS& as, uint32_t asn) {
    return std::find(as.peers.begin(), as.peers.end(), asn) != as.peers.end();
}

static ASGraph graphFromString(const std::string& data) {
    std::istringstream ss(data);
    return ASGraph::fromStream(ss);
}

// ── tests ─────────────────────────────────────────────────────────────────────

// Simple linear chain: 1 (provider) → 2 → 3 (leaf)
static void test_basic_pc_relationships() {
    ASGraph g;
    g.addProviderCustomer(1, 2);
    g.addProviderCustomer(2, 3);

    check("chain: AS 1 exists",        g.ases.count(1) == 1);
    check("chain: AS 2 exists",        g.ases.count(2) == 1);
    check("chain: AS 3 exists",        g.ases.count(3) == 1);
    check("chain: 2 is customer of 1", hasCustomer(g.ases.at(1), 2));
    check("chain: 1 is provider of 2", hasProvider(g.ases.at(2), 1));
    check("chain: 3 is customer of 2", hasCustomer(g.ases.at(2), 3));
    check("chain: 2 is provider of 3", hasProvider(g.ases.at(3), 2));
    check("chain: 1 has no providers", g.ases.at(1).providers.empty());
    check("chain: 3 has no customers", g.ases.at(3).customers.empty());
}

// Peer relationships are bidirectional.
static void test_peer_relationships() {
    ASGraph g;
    g.addPeer(10, 20);

    check("peer: AS 10 has AS 20 as peer", hasPeer(g.ases.at(10), 20));
    check("peer: AS 20 has AS 10 as peer", hasPeer(g.ases.at(20), 10));
    check("peer: AS 10 has no providers", g.ases.at(10).providers.empty());
    check("peer: AS 10 has no customers", g.ases.at(10).customers.empty());
}

// A valid DAG (no cycle) should not trigger cycle detection.
static void test_no_false_positive_simple() {
    ASGraph g;
    g.addProviderCustomer(1, 2);
    g.addProviderCustomer(1, 3);
    g.addProviderCustomer(2, 4);
    g.addProviderCustomer(3, 4); // diamond

    check("diamond DAG: no cycle", !g.hasCycle());
}

// Direct cycle: A→B, B→A in the provider-customer direction.
static void test_direct_cycle() {
    ASGraph g;
    g.addProviderCustomer(1, 2); // 1 is provider of 2
    g.addProviderCustomer(2, 1); // 2 is provider of 1 → cycle

    check("direct cycle: detected", g.hasCycle());
}

// Three-node cycle: 1 provides 2, 2 provides 3, 3 provides 1.
static void test_three_node_cycle() {
    ASGraph g;
    g.addProviderCustomer(1, 2);
    g.addProviderCustomer(2, 3);
    g.addProviderCustomer(3, 1);

    check("3-node cycle: detected", g.hasCycle());
}

// Peer cycles must NOT be flagged (they are expected and valid).
static void test_peer_cycle_not_flagged() {
    ASGraph g;
    // Triangular peering (common in the real internet)
    g.addPeer(1, 2);
    g.addPeer(2, 3);
    g.addPeer(3, 1);
    // Add a legitimate p-c relationship so the graph isn't trivially flat
    g.addProviderCustomer(4, 1);
    g.addProviderCustomer(4, 2);

    check("peer cycle: not flagged as cycle", !g.hasCycle());
}

// A cycle that is not at the root — embedded in a larger valid graph.
static void test_embedded_cycle() {
    ASGraph g;
    g.addProviderCustomer(100, 1); // 100 provides to 1
    g.addProviderCustomer(1, 2);
    g.addProviderCustomer(2, 3);
    g.addProviderCustomer(3, 2); // cycle between 2 and 3

    check("embedded cycle: detected", g.hasCycle());
}

// A valid multi-root graph (several top-level providers) should be clean.
static void test_multiple_roots_no_cycle() {
    ASGraph g;
    g.addProviderCustomer(1, 10);
    g.addProviderCustomer(2, 10);
    g.addProviderCustomer(2, 11);
    g.addProviderCustomer(3, 11);
    g.addPeer(1, 2);
    g.addPeer(2, 3);

    check("multi-root DAG: no cycle",    !g.hasCycle());
    check("multi-root DAG: 5 ASes",      g.size() == 5);
    check("multi-root: 10 has 2 provs",  g.ases.at(10).providers.size() == 2);
}

// Parse a CAIDA-formatted string and verify the graph it produces.
static void test_parse_caida_format() {
    const std::string caida =
        "# comment line\n"
        "1|2|-1|bgp\n"   // 1 is provider of 2
        "1|3|-1|bgp\n"   // 1 is provider of 3
        "4|5|0|bgp\n"    // 4 and 5 are peers
        "# another comment\n"
        "2|6|-1|bgp\n";  // 2 is provider of 6

    ASGraph g = graphFromString(caida);

    check("parse: 6 ASes loaded",             g.size() == 6);
    check("parse: 2 is customer of 1",        hasCustomer(g.ases.at(1), 2));
    check("parse: 3 is customer of 1",        hasCustomer(g.ases.at(1), 3));
    check("parse: 1 is provider of 2",        hasProvider(g.ases.at(2), 1));
    check("parse: 6 is customer of 2",        hasCustomer(g.ases.at(2), 6));
    check("parse: 4 and 5 are peers",         hasPeer(g.ases.at(4), 5) && hasPeer(g.ases.at(5), 4));
    check("parse: no cycle",                  !g.hasCycle());
}

// Parse a string that contains a cycle and confirm it is caught.
static void test_parse_cycle_detected() {
    const std::string caida =
        "1|2|-1|bgp\n"
        "2|3|-1|bgp\n"
        "3|1|-1|bgp\n"; // 3 provides to 1 → cycle

    ASGraph g = graphFromString(caida);
    check("parse+cycle: cycle detected", g.hasCycle());
}

// ── integration: real CAIDA file ──────────────────────────────────────────────

static void test_real_caida_file(const std::string& path) {
    std::cout << "\n[integration] loading " << path << " ...\n";
    ASGraph g;
    try {
        g = ASGraph::fromFile(path);
    } catch (const std::exception& e) {
        std::cout << "[SKIP] " << e.what() << "\n";
        return;
    }

    check("real CAIDA: > 70000 ASes",    g.size() > 70000);
    check("real CAIDA: < 120000 ASes",   g.size() < 120000);
    check("real CAIDA: no cycle",        !g.hasCycle());

    // Spot-check a well-known transit AS (Limelight / AS 22822 or similar).
    // AS 1 appears in the file as a peer of 11537.
    check("real CAIDA: AS 1 exists",     g.ases.count(1) == 1);
}

// ── entry point ───────────────────────────────────────────────────────────────

int main(int argc, char* argv[]) {
    test_basic_pc_relationships();
    test_peer_relationships();
    test_no_false_positive_simple();
    test_direct_cycle();
    test_three_node_cycle();
    test_peer_cycle_not_flagged();
    test_embedded_cycle();
    test_multiple_roots_no_cycle();
    test_parse_caida_format();
    test_parse_cycle_detected();

    // Optional: pass a pre-decompressed CAIDA file as argv[1].
    if (argc >= 2)
        test_real_caida_file(argv[1]);

    std::cout << "\n" << passed << " passed, " << failed << " failed\n";
    return failed == 0 ? 0 : 1;
}
