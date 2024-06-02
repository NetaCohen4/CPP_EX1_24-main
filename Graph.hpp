/*
    325195774
    netaco432@gmail.com
*/

// Graph.hpp

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <stdexcept>
#include <limits>
using namespace std;

const int INF = std::numeric_limits<int>::max(); // Infinity for dijkstra

namespace ariel {

    class Graph {
    private:

        vector<vector<int>> graph;
        size_t n = 0;

    public:

        Graph() {}

        Graph(vector<vector<int>> myGraph) {
            loadGraph(myGraph);
        }

        size_t getSize() {
            return n;
        }

        vector<vector<int>> getGraph() {
            return graph;
        }

        // Function to load graph data from file
        void loadGraph(std::vector<std::vector<int>> matrix) {
            size_t numRows = matrix.size();
            if (numRows == 0) // If the matrix has no rows, it's not a square matrix
                throw std::invalid_argument("Invalid graph: Empty matrix"); // Throw an exception if the matrix is empty
            for (size_t i = 0; i < numRows; i++) {
                if (matrix[i].size() != numRows)
                    throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
            }
            for (size_t i = 0; i < numRows; i++) {
                if (matrix[i][i]) {
                    throw std::invalid_argument("Invalid graph: A vertex can't have an edge to itself.");
                }
            }
            graph = matrix;
            n = numRows;
            
        }

        // Function to print the graph
        void printGraph(){
            int e_count = 0;
            for (const auto& row : graph) {
                for (int value : row) {
                    if (value != 0) {
                        e_count++;
                    }
                }
            }
            std::cout << "Graph with " <<  graph.size() << " vertices and " << e_count << " edges.\n";
        }

        //bool dfs(size_t node, vector<bool>& visited, vector<size_t>& parent, string& cycle);

        //bool Bellman_Ford_Negative_Cycle();

        //bool isBipartite();

    };

}


#endif // GRAPH_HPP