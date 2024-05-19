/*
    325195774
    netaco432@gmail.com
*/

// Graph.cpp

#include <iostream>
#include "Graph.hpp"
#include <queue>
#include <vector>
#include <stdexcept>

namespace ariel {
/*
    // Function to load graph data from file
    void Graph::loadGraph(std::vector<std::vector<int>> matrix) {
        size_t numRows = matrix.size();
        if (numRows == 0) // If the matrix has no rows, it's not a square matrix
            throw std::invalid_argument("Invalid graph: Empty matrix"); // Throw an exception if the matrix is empty
        size_t numCols = matrix[0].size(); // Assuming all rows have same number of columns
        if (numRows != numCols)
            throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
        for (size_t i = 0; i < numRows; i++) {
            if (graph[i][i]) {
                throw std::invalid_argument("Invalid graph: A vertex can't have an edge to itself.");
            }
        }
        graph = matrix;
        n = graph.size();
            
    } 

    void Graph::printGraph(){
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
    */  

    bool Graph::is_BFS_cover_all(size_t start) {

        std::vector<bool> visited(n, false);
        std::queue<int> queue;

        // Start BFS from the start vertex
        queue.push(start);
        visited[start] = true;

        while (!queue.empty()) {
            size_t currentVertex = (size_t)queue.front();
            queue.pop();

            // Visit all adjacent vertices
            for (size_t neighbor = 0; neighbor < n; neighbor++) {
                if (graph[currentVertex][neighbor])
                {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        queue.push(neighbor);
                    }
                }
            }
        }
        for (bool v : visited) {
            if (!v) {
                return false;
            }
        }
        return true;
    }

    vector<int> Graph::dijkstra(size_t start, vector<size_t>& parent) {

        vector<int> dist(n, INF);
        vector<bool> visited(n, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // min-heap for maintaining shortest distances

        parent[start] = start;
        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            size_t u = (size_t)pq.top().second;
            pq.pop();
            if (visited[u]) continue;
            visited[u] = true;

            for (size_t v = 0; v < n; ++v) {
                if (graph[u][v] != 0) {
                    int alt = dist[u] + graph[u][v];
                    if (alt < dist[v]) {
                        dist[v] = alt;
                        parent[v] = u; // Update predecessor of v
                        pq.push({dist[v], v});
                    }
                }
            }
        }

        return dist;
    }


    bool Graph::dfs(size_t node, vector<bool>& visited, vector<size_t>& parent, string& cycle) {
        visited[node] = true;
        for (size_t i = 0; i < n; i++) {
            if (graph[node][i]) {
                if (visited[i]) {
                    if (i != parent[node]) {
                        size_t cur = node;
                        cycle = to_string(i);
                        while (cur != i) {
                            cycle = to_string(cur) + "->" + cycle;
                            cur = parent[cur];
                        }
                        cycle = to_string(i) + "->" + cycle;
                        return true;
                    }
                }
                else {
                    parent[i] = node;
                    if (dfs(i, visited, parent, cycle)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    bool Graph::Bellman_Ford_Negative_Cycle() {
        vector<int> dist(n, INF);

        // 0 as the source vertex
        dist[0] = 0;

        // Relax all edges |V| - 1 times
        for (size_t i = 0; i < n - 1; ++i) {
            for (size_t u = 0; u < n; ++u) {
                for (size_t v = 0; v < graph[u].size(); ++v) {
                    if (graph[u][v] != 0) { // 0 represents absence of edge
                        if (dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                            dist[v] = dist[u] + graph[u][v];
                        }
                    }
                }
            }
        }

        // Check for negative cycles
        for (size_t u = 0; u < n; ++u) {
            for (size_t v = 0; v < graph[u].size(); ++v) {
                if (graph[u][v] != 0) { // 0 represents absence of edge
                    if (dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                        return true; // Negative cycle detected
                    }
                }
            }
        }

        return false; // No negative cycle detected
    }

    bool Graph::isBipartite() {

        vector<int> color(n, -1); // Initialize colors (-1: not colored, 0: color 1, 1: color 2)
        queue<size_t> q;

        for (size_t start = 0; start < n; ++start) {
            if (color[start] == -1) {
                color[start] = 0; // Assign color 1 to start node
                q.push(start);

                while (!q.empty()) {
                    size_t u = q.front();
                    q.pop();

                    for (size_t v = 0; v < n; ++v) {
                        if (graph[u][v] == 0) {
                            continue; // No edge between u and v
                        }

                        if (color[v] == -1) {
                            color[v] = 1 - color[u]; // Assign opposite color to neighbor v
                            q.push(v);
                        } else if (color[v] == color[u]) {
                            return false; // Found an edge between nodes of the same color (not bipartite)
                        }
                    }
                }
            }
        }

        return true; // All nodes are colored without conflicts (bipartite)
    }

}