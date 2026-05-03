#pragma once
#include "as.hpp"
#include <istream>
#include <string>
#include <unordered_map>
#include <vector>

class ASGraph {
public:
    std::unordered_map<uint32_t, AS> ases;
    std::vector<std::vector<uint32_t>> ranks;

    void addProviderCustomer(uint32_t provider_asn, uint32_t customer_asn);
    void addPeer(uint32_t asn1, uint32_t asn2);
    bool hasCycle() const;
    void flatten();
    void seedAnnouncements(const std::string& filename);
    void applyROV(const std::string& filename);
    void propagate();
    void outputCSV(const std::string& filename) const;

    static ASGraph fromStream(std::istream& in);
    static ASGraph fromFile(const std::string& filename);
    size_t size() const { return ases.size(); }
};
