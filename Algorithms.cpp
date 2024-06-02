/*
    325195774
    netaco432@gmail.com
*/

#include <iostream>
#include "Graph.hpp"
#include "Algorithms.hpp"
#include <limits>
#include <queue>
#include <vector>
using namespace std;


namespace ariel {

    bool Algorithms::is_BFS_cover_all(Graph g, size_t start) {

        vector<vector<int>> graph = g.getGraph();
        size_t n = g.getSize();

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
    

    // Function to check whether a graph is connected
    bool Algorithms::isConnected(Graph g) {
        if (g.getSize() < 2) {
            return true;
        }
        return is_BFS_cover_all(g, 0) && is_BFS_cover_all(g, 1);
    }


    vector<int> Algorithms::dijkstra(Graph g, size_t start, vector<size_t>& parent) {

        vector<vector<int>> graph = g.getGraph();
        size_t n = g.getSize();

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


    string Algorithms::shortestPath(Graph g, size_t start, size_t end) {
        if (start == end) {
            return to_string(start);
        }
        vector<size_t> parent(g.getSize(), INF);
        vector<int> dist = dijkstra(g, start, parent);
        if (dist[end] == INF) {
            return "-1";
        }
        string ans = "Shortest path from " + to_string(start) + " to "+to_string(end) + ": ";
        string path = to_string(end);
        while (parent[end] != start){
            path = to_string(parent[end]) + "->" + path;
            end = parent[end];
        }
        path = to_string(parent[end]) + "->" + path;

        return ans + path;

    }


    // Running dfs over a graph to find cycle
    bool Algorithms::dfs(Graph g, size_t start, vector<bool>& visited, vector<size_t>& parent, string& cycle) {
        vector<vector<int>> graph = g.getGraph();
        size_t n = g.getSize();
        
        visited[start] = true;
        for (size_t i = 0; i < n; i++) {
            if (graph[start][i]) {
                if (visited[i]) {
                    if (i != parent[start]) {
                        size_t cur = start;
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
                    parent[i] = start;
                    if (dfs(g, i, visited, parent, cycle)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }


    string Algorithms::isContainsCycle(Graph g) {
        size_t n = g.getSize();
        vector<bool> visited(n, false);
        vector<size_t> parent(n, INF);
        string cycle;
    
        for (size_t i = 0; i < n; ++i) {
            if (!visited[i] && dfs(g, i, visited, parent, cycle)) {
                return "The cycle is: " + cycle;
            }
        }
        
        return "No cycle found.";
    }


    string Algorithms::isBipartite(Graph g) { // האלגוריתם מקבל גרף ומחזיר את החלוקה של הגרף לגרף דו-צדדי. אם אי אפשר לחלק את הגרף, האלגוריתם יחזיר 0.
    
        vector<vector<int>> graph = g.getGraph();
        size_t n = g.getSize();
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
                        if (graph[u][v] != 0) { // If there is an edge between u and v
                            if (color[v] == -1) { // If v is not colored
                                color[v] = 1 - color[u]; // Assign opposite color to neighbor v
                                q.push(v);
                            } else if (color[v] == color[u]) {
                                return "0"; // Found an edge between nodes of the same color (not bipartite)
                            }
                        }

                        
                    }
                }
            }
        }
        string A = "A={";
        string B = "B={";
        bool flagA = true, flagB = true;
        for (size_t i = 0; i < n; ++i) {
            if (color[i]) {
                if (flagB)
                    B += to_string(i);
                else 
                    B += ", " + to_string(i);
                flagB = false;
            }
            else {
                if (flagA)
                    A += to_string(i);
                else 
                    A += ", " + to_string(i);
                flagA = false;
            }
        }
        A += "}, ";
        B += "}";
        return "The graph is bipartite: " + A + B; // All nodes are colored without conflicts (bipartite)
    }


    // Algorithm to find negative cycle in an array using Bellman-Ford algorithm
    bool Algorithms::negativeCycle(Graph g) {

        vector<vector<int>> graph = g.getGraph();
        size_t n = g.getSize();
        vector<int> dist(n, INF);

        // 0 as the source vertex
        dist[0] = 0;

        // Relax all edges |V| - 1 times
        for (size_t i = 0; i < n - 1; ++i) {
            for (size_t u = 0; u < n; ++u) {
                for (size_t v = 0; v < n; ++v) {
                    if (graph[u][v] != 0) { // 0 represents absence of edge
                        if (dist[u] + graph[u][v] < dist[v]) {
                            dist[v] = dist[u] + graph[u][v];
                        }
                    }
                }
            }
        }

        // Check for negative cycles
        for (size_t u = 0; u < n; ++u) {
            for (size_t v = 0; v < n; ++v) {
                if (graph[u][v] != 0) { // 0 represents absence of edge
                    if (dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                        return true; // Negative cycle detected
                    }
                }
            }
        }

        return false; // No negative cycle found
    }


}