#pragma once
#include <vector>
#include <unordered_map>

class Graph {
    private:
        void deep_first_search_alg(int node, std::vector<bool> &visited,
                std::unordered_map<int, std::vector<int>> &adj);

    public:
        int countComponents(int n, std::vector<std::vector<int>> &edges);
};

void Graph::deep_first_search_alg(int noeud, std::vector<bool> &visited,
                std::unordered_map<int, std::vector<int>> &adj) {
    visited[noeud] = true;
    for (int voisin : adj[noeud]) {
        if (!visited[voisin]) {
            deep_first_search_alg(voisin, visited, adj);
        }
    }
}

int Graph::countComponents(int n, std::vector<std::vector<int>> &edges) {
    std::unordered_map<int, std::vector<int>> adj;
    std::vector<bool> visited(n, false);
    int comp = 0;

    for (const auto& edge : edges) {
        adj[edge[0]].push_back(edge[1]);
        adj[edge[1]].push_back(edge[0]);
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            deep_first_search_alg(i, visited, adj);
            comp++;
        }
    }

    return comp;
}