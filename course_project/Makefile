CXX      = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra
SRC      = as_graph.cpp policy.cpp
HEADERS  = as.hpp as_graph.hpp announcement.hpp policy.hpp

all: bgp_sim run_tests

bgp_sim: main.cpp $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o bgp_sim main.cpp $(SRC)

run_tests: test_graph.cpp $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o run_tests test_graph.cpp $(SRC)

clean:
	rm -f bgp_sim run_tests
