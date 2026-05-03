#pragma once
#include <cstdint>
#include <string>
#include <vector>

enum class Relationship { ORIGIN = 0, CUSTOMER = 1, PEER = 2, PROVIDER = 3 };

struct Announcement {
    std::string prefix;
    std::vector<uint32_t> as_path;
    uint32_t next_hop_asn;
    Relationship recv_relationship;
    bool rov_invalid;
};
