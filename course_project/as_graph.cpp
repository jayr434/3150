#include "as_graph.hpp"
#include <fstream>
#include <queue>
#include <stdexcept>
#include <string>

static void stripCR(std::string& s) {
    if (!s.empty() && s.back() == '\r') s.pop_back();
}

void ASGraph::addProviderCustomer(uint32_t provider_asn, uint32_t customer_asn) {
    ases[provider_asn].asn = provider_asn;
    ases[customer_asn].asn = customer_asn;
    ases[provider_asn].customers.push_back(customer_asn);
    ases[customer_asn].providers.push_back(provider_asn);
}

void ASGraph::addPeer(uint32_t asn1, uint32_t asn2) {
    ases[asn1].asn = asn1;
    ases[asn2].asn = asn2;
    ases[asn1].peers.push_back(asn2);
    ases[asn2].peers.push_back(asn1);
}

// Kahn's algorithm on provider-customer edges only.
// In-degree = number of customers. If we can't process all nodes, there's a cycle.
bool ASGraph::hasCycle() const {
    std::unordered_map<uint32_t, int> in_degree;
    in_degree.reserve(ases.size());
    for (const auto& [asn, as] : ases)
        in_degree[asn] = static_cast<int>(as.customers.size());

    std::queue<uint32_t> q;
    for (const auto& [asn, deg] : in_degree)
        if (deg == 0) q.push(asn);

    int processed = 0;
    while (!q.empty()) {
        uint32_t cur = q.front(); q.pop();
        ++processed;
        for (uint32_t provider : ases.at(cur).providers)
            if (--in_degree[provider] == 0)
                q.push(provider);
    }

    return processed != static_cast<int>(ases.size());
}

void ASGraph::flatten() {
    ranks.clear();

    std::unordered_map<uint32_t, int> in_degree;
    in_degree.reserve(ases.size());
    for (const auto& [asn, as] : ases)
        in_degree[asn] = static_cast<int>(as.customers.size());

    std::vector<uint32_t> current;
    for (const auto& [asn, deg] : in_degree)
        if (deg == 0) current.push_back(asn);

    while (!current.empty()) {
        ranks.push_back(current);
        std::vector<uint32_t> next;
        for (uint32_t asn : current)
            for (uint32_t provider : ases.at(asn).providers)
                if (--in_degree[provider] == 0)
                    next.push_back(provider);
        current = std::move(next);
    }
}

void ASGraph::seedAnnouncements(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Cannot open announcements file: " + filename);

    std::string line;
    std::getline(file, line); // skip header

    while (std::getline(file, line)) {
        stripCR(line);
        if (line.empty()) continue;

        size_t p1 = line.find(',');
        size_t p2 = line.find(',', p1 + 1);
        if (p1 == std::string::npos || p2 == std::string::npos) continue;

        uint32_t seed_asn = static_cast<uint32_t>(std::stoul(line.substr(0, p1)));
        std::string prefix = line.substr(p1 + 1, p2 - p1 - 1);
        std::string rov_str = line.substr(p2 + 1);
        bool rov_invalid = (rov_str == "True" || rov_str == "true");

        Announcement ann;
        ann.prefix = prefix;
        ann.as_path = {seed_asn};
        ann.next_hop_asn = seed_asn;
        ann.recv_relationship = Relationship::ORIGIN;
        ann.rov_invalid = rov_invalid;

        auto it = ases.find(seed_asn);
        if (it != ases.end())
            it->second.policy->local_rib[prefix] = std::move(ann);
    }
}

void ASGraph::applyROV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Cannot open ROV file: " + filename);

    std::string line;
    while (std::getline(file, line)) {
        stripCR(line);
        if (line.empty()) continue;
        uint32_t asn = static_cast<uint32_t>(std::stoul(line));
        auto it = ases.find(asn);
        if (it != ases.end()) {
            auto old_rib = std::move(it->second.policy->local_rib);
            it->second.policy = std::make_unique<ROVPolicy>();
            it->second.policy->local_rib = std::move(old_rib);
        }
    }
}

static void sendAnnouncements(const AS& sender, AS& receiver, Relationship rel) {
    for (const auto& [prefix, ann] : sender.policy->local_rib) {
        Announcement to_send = ann;
        to_send.next_hop_asn = sender.asn;
        to_send.recv_relationship = rel;
        receiver.policy->receive(to_send);
    }
}

void ASGraph::propagate() {
    // up: rank 0 to max
    for (size_t r = 0; r < ranks.size(); ++r) {
        if (r > 0) {
            for (uint32_t asn : ranks[r])
                ases[asn].policy->process(asn);
        }
        for (uint32_t asn : ranks[r]) {
            AS& sender = ases[asn];
            for (uint32_t provider_asn : sender.providers)
                sendAnnouncements(sender, ases[provider_asn], Relationship::CUSTOMER);
        }
    }

    // across: all send to peers, then all process
    for (auto& [asn, as] : ases)
        for (uint32_t peer_asn : as.peers)
            sendAnnouncements(as, ases[peer_asn], Relationship::PEER);
    for (auto& [asn, as] : ases)
        as.policy->process(asn);

    // down: max rank to 0
    for (int r = static_cast<int>(ranks.size()) - 1; r >= 0; --r) {
        for (uint32_t asn : ranks[r]) {
            AS& sender = ases[asn];
            for (uint32_t customer_asn : sender.customers)
                sendAnnouncements(sender, ases[customer_asn], Relationship::PROVIDER);
        }
        if (r > 0) {
            for (uint32_t asn : ranks[r - 1])
                ases[asn].policy->process(asn);
        }
    }
}

static std::string formatAsPath(const std::vector<uint32_t>& path) {
    std::string result = "\"(";
    for (size_t i = 0; i < path.size(); ++i) {
        if (i > 0) result += ", ";
        result += std::to_string(path[i]);
    }
    if (path.size() == 1) result += ",";
    result += ")\"";
    return result;
}

void ASGraph::outputCSV(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Cannot open output file: " + filename);

    file << "asn,prefix,as_path\n";
    for (const auto& [asn, as] : ases) {
        for (const auto& [prefix, ann] : as.policy->local_rib)
            file << asn << "," << prefix << "," << formatAsPath(ann.as_path) << "\n";
    }
}

ASGraph ASGraph::fromStream(std::istream& in) {
    ASGraph graph;
    graph.ases.reserve(100000);

    std::string line;
    while (std::getline(in, line)) {
        stripCR(line);
        if (line.empty() || line[0] == '#') continue;

        size_t p1 = line.find('|');
        if (p1 == std::string::npos) continue;
        size_t p2 = line.find('|', p1 + 1);
        if (p2 == std::string::npos) continue;
        size_t p3 = line.find('|', p2 + 1);
        if (p3 == std::string::npos) continue;

        uint32_t asn1 = static_cast<uint32_t>(std::stoul(line.substr(0, p1)));
        uint32_t asn2 = static_cast<uint32_t>(std::stoul(line.substr(p1 + 1, p2 - p1 - 1)));
        int rel = std::stoi(line.substr(p2 + 1, p3 - p2 - 1));

        if (rel == -1)
            graph.addProviderCustomer(asn1, asn2);
        else if (rel == 0)
            graph.addPeer(asn1, asn2);
    }

    return graph;
}

ASGraph ASGraph::fromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Cannot open topology file: " + filename);
    return fromStream(file);
}
