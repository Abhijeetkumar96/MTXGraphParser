CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall

# Targets
all: mtxToEdgelist EdgeAdderForConnectivity

mtxToEdgelist: mtxToEdgelist.cpp
	$(CXX) $(CXXFLAGS) -fopenmp mtxToEdgelist.cpp -o mtxToEdgelist

EdgeAdderForConnectivity: EdgeAdderForConnectivity.cpp
	$(CXX) $(CXXFLAGS) EdgeAdderForConnectivity.cpp -o EdgeAdderForConnectivity

clean:
	rm -f mtxToEdgelist EdgeAdderForConnectivity
