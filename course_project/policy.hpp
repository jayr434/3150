#pragma once
#include "announcement.hpp"
#include <string>
#include <unordered_map>
#include <vector>

class Policy {
public:
    std::unordered_map<std::string, Announcement> local_rib;
    std::unordered_map<std::string, std::vector<Announcement>> recv_queue;

    virtual ~Policy() = default;
    virtual void receive(const Announcement& ann);
    void process(uint32_t my_asn);
    static bool isBetter(const Announcement& a, const Announcement& b);
};

class BGPPolicy : public Policy {};

class ROVPolicy : public BGPPolicy {
public:
    void receive(const Announcement& ann) override;
};
