#pragma once
#include "policy.hpp"
#include <cstdint>
#include <memory>
#include <vector>

struct AS {
    uint32_t asn;
    std::vector<uint32_t> providers;
    std::vector<uint32_t> customers;
    std::vector<uint32_t> peers;
    std::unique_ptr<Policy> policy;

    AS() : asn(0), policy(std::make_unique<BGPPolicy>()) {}
    explicit AS(uint32_t asn) : asn(asn), policy(std::make_unique<BGPPolicy>()) {}
};
