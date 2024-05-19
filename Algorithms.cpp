/*
    325195774
    netaco432@gmail.com
*/

#include <iostream>
#include "Graph.hpp"
#include "Algorithms.hpp"
#include <limits>
using namespace std;


namespace ariel {
    
    // Function to check if the graph is connected
    bool Algorithms::isConnected(Graph g) {
        if (g.getSize() < 2) {
            return true;
        }
        return (g.is_BFS_cover_all(0) && g.is_BFS_cover_all(1));
    }

    string Algorithms::shortestPath(Graph g, size_t start, size_t end) {
        if (start == end) {
            return to_string(start);
        }
        vector<size_t> parent(g.getSize(), INF);
        vector<int> dist = g.dijkstra(start, parent);
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

    string Algorithms::isContainsCycle(Graph g) {
        size_t n = g.getSize();
        vector<bool> visited(n, false);
        vector<size_t> parent(n, INF);
        string cycle;
    
        for (size_t i = 0; i < n; ++i) {
            if (!visited[i] && g.dfs(i, visited, parent, cycle)) {
                return cycle;
            }
        }
        
        return "No cycle found.";
    }

    bool Algorithms::isBipartite(Graph g) { // האלגוריתם מקבל גרף ומחזיר את החלוקה של הגרף לגרף דו-צדדי. אם אי אפשר לחלק את הגרף, האלגוריתם יחזיר 0.
        return g.isBipartite();
    }


    bool Algorithms::negativeCycle(Graph g) {
        return g.Bellman_Ford_Negative_Cycle();
    }


}