/**
 * @file EdgeAdderForConnectivity.cpp
 * @brief Finds the number of connected components in a graph and connects them if more than one.
 * 
 * This program takes a graph, represented as a set of edges and vertices, and identifies
 * all connected components. If the graph is not fully connected (i.e., has more than one
 * connected component), the program will add the minimum number of edges required to make
 * the graph fully connected.
 * 
 * @author Abhijeet
 * @date Nov 18, 2023
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

// Function to perform breadth-first search (BFS)
void bfs(int node, const std::vector<std::vector<int>>& adjList, std::vector<bool>& visited) {
    std::queue<int> q;
    q.push(node);
    visited[node] = true;

    while (!q.empty()) {
        int currNode = q.front();
        q.pop();

        for (int neighbor : adjList[currNode]) {
            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
}

// Function to find the number of connected components in the graph
int findConnectedComponents(const std::vector<std::vector<int>>& adjList, std::vector<std::pair<int, int>>& edgesToAdd) {
    int numNodes = adjList.size();
    std::vector<bool> visited(numNodes, false);
    int numComponents = 0;
    for (int node = 0; node < numNodes; ++node) {
        if (!visited[node]) {
            bfs(node, adjList, visited);
            if(node != 0) {
                edgesToAdd.push_back(std::make_pair(0, node));
                edgesToAdd.push_back(std::make_pair(node, 0));
            }
            numComponents++;
        }
    }

    return numComponents;
}

// Function to add new edges to the existing graph & update the numEdges
void makeFullyConnected(const std::string filename, const std::vector<std::pair<int, int>>& edgesToAdd, int numVert, int numEdges) {

    numEdges+= edgesToAdd.size();
     // Step 1: Overwrite the starting line if the length is the same
    std::fstream file(filename, std::ios::in | std::ios::out);
    if (file.is_open()) {
        file.seekp(0, std::ios::beg); // Move to the beginning of the file
        file << numVert <<" " << numEdges << std::endl; // Overwrite the first line
        file.close();
    } else {
        std::cerr << "Unable to open file." << std::endl;
        return;
    }

    // Open the file in append mode
    std::ofstream outFile(filename, std::ios::app);

    if (outFile.is_open()) {
        for(const auto &i : edgesToAdd)
            outFile << i.first <<" " << i.second << std::endl;
        outFile.close();
    } else {
        std::cerr << "Unable to open file for appending." << std::endl;
    }
}

int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);
    if(argc < 2)
    {
        std::cerr << "Usage : " << argv[0] <<" filename ";
        return 0;
    }
    std::string filename = argv[1];
    std::ifstream inputFile(filename);

    if (inputFile.is_open()) {
        int numNodes, numEdges;
        inputFile >> numNodes >> numEdges;

        std::vector<std::vector<int>> adjList(numNodes);

        for (int i = 0; i < numEdges; ++i) {
            int u, v;
            inputFile >> u >> v;
            if(u == v)
                continue;
            adjList[u].push_back(v);
        }

        inputFile.close();

        #ifdef DEBUG
            for(int i = 0; i < adjList.size(); ++i) {
                std::cout << i <<" : ";
                for(auto const& j : adjList[i])
                    std::cout << j <<" ";
                std::cout << std::endl;
            }
        #endif

        std::vector<std::pair<int, int>> edgesToAdd;
        int numComponents = findConnectedComponents(adjList, edgesToAdd);

        if(numComponents > 1)
            makeFullyConnected(filename, edgesToAdd, numNodes, numEdges);

        #ifdef DEBUG
            std::cout <<"edgesToAdd size = " << edgesToAdd.size() << std::endl;
            for(const auto &i : edgesToAdd)
                std::cout << i.first <<" " << i.second << std::endl;
        #endif

        std::cout << "Number of connected components: " << numComponents << std::endl;
    } else {
        std::cout << "Unable to open the input file." << std::endl;
    }

    return 0;
}
