#include "policy.hpp"

void Policy::receive(const Announcement& ann) {
    recv_queue[ann.prefix].push_back(ann);
}

void Policy::process(uint32_t my_asn) {
    for (auto& [prefix, anns] : recv_queue) {
        for (auto& ann : anns) {
            Announcement stored = ann;
            stored.as_path.insert(stored.as_path.begin(), my_asn);

            auto it = local_rib.find(prefix);
            if (it == local_rib.end() || isBetter(stored, it->second))
                local_rib[prefix] = std::move(stored);
        }
    }
    recv_queue.clear();
}

bool Policy::isBetter(const Announcement& a, const Announcement& b) {
    if (a.recv_relationship != b.recv_relationship)
        return a.recv_relationship < b.recv_relationship;
    if (a.as_path.size() != b.as_path.size())
        return a.as_path.size() < b.as_path.size();
    return a.next_hop_asn < b.next_hop_asn;
}

void ROVPolicy::receive(const Announcement& ann) {
    if (ann.rov_invalid) return;
    Policy::receive(ann);
}
