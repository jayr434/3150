CXX = g++
CXXFLAGS = -std=c++17 -g

solution: solution.cpp
	$(CXX) $(CXXFLAGS) -o solution solution.cpp

test: solution
	pytest test_game.py

clean:
	rm -f solution game_output.csv
