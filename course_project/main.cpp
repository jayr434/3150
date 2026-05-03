#include "as_graph.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 5) {
        std::cerr << "Usage: " << argv[0]
                  << " <topology_file> <anns.csv> <rov_asns.csv> <output.csv>\n";
        return 1;
    }

    const std::string topology_file = argv[1];
    const std::string anns_file     = argv[2];
    const std::string rov_file      = argv[3];
    const std::string output_file   = argv[4];

    ASGraph graph;
    try {
        graph = ASGraph::fromFile(topology_file);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    if (graph.hasCycle()) {
        std::cerr << "Error: cycle detected in provider-customer relationships\n";
        return 1;
    }

    graph.flatten();
    graph.seedAnnouncements(anns_file);
    graph.applyROV(rov_file);
    graph.propagate();
    graph.outputCSV(output_file);

    return 0;
}
