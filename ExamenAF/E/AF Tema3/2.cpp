// Folosindu-ne de Problema1 (MaxFlow) adaugam un nod de start 0 si unul de destinatie n+m+1
// nodul de start il conectam la toate nodurile din prima grupa cu capacitate 0
// nodurile din a doua grupa le conectam la destinatie cu capacitate 1

// Punem capacitate 1 intre toate nodurile ce duc din grupa 1 in grupa 2
// Calculam MaxFlow pe reteaua creata
// Muchiile ce duc din prima grupa in a doua si au MaxFlow 1, sunt muchiile care fac parte din cuplajul maxim
// MaxFlow e cuplajul maxim

#include <bits/stdc++.h>

using namespace std;

ifstream in("cuplaj.in");
ofstream out("cuplaj.out");

int n, m, e, start, final;

vector<vector<pair<pair<int, int>, int>>> graph;
vector<pair<int, int>> parent;
vector<bool> visited;

bool bfs() {
    visited.assign(final + 1, false);
    parent.assign(final + 1, {-1, -1});
    queue<int> q;

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int currentNode = q.front();
        q.pop();
        if (currentNode == final)
            return true;

        int poz = 0;
        for (auto const &neigh: graph[currentNode]) {
            int neighbor = neigh.first.first;
            int capacity = neigh.first.second;
            if (visited[neighbor] == 0 && capacity > 0) {
                visited[neighbor] = true;
                parent[neighbor] = {currentNode, poz};
                q.push(neighbor);
            }
            poz++;
        }
    }
    return false;
}

// Algoritmul lui Edmonds Karp
int EdK() {

    int maxFlow = 0;

    while (bfs()) {
        for (auto const &neigh: graph[final]) {
            int node = neigh.first.first;
            int capacity = graph[node][neigh.second].first.second;

            if (capacity > 0 && visited[node]) {

                parent[final] = {node, neigh.second};

                int minFlow = INT_MAX;
                int i = final, x, y;

                while (parent[i].first != -1) {
                    x = parent[i].first;
                    y = parent[i].second;
                    minFlow = min(minFlow, graph[x][y].first.second);
                    i = x;
                }

                i = final;
                while (parent[i].first != -1) {
                    x = parent[i].first;
                    y = parent[i].second;
                    int z = graph[x][y].second;
                    graph[x][y].first.second -= minFlow;
                    graph[i][z].first.second += minFlow;
                    i = x;
                }

                maxFlow += minFlow;
            }
        }
    }
    return maxFlow;
}

int main() {

    in >> n >> m >> e;

    start = 0;
    final = n + m + 1;

    graph.resize(final + 1);
    parent.resize(final + 1);
    visited.resize(final + 1);

    for (int i = 0; i < e; i++) {
        int x, y;
        in >> x >> y;
        graph[x].push_back({{y + n, 1}, graph[y + n].size()});
        graph[y + n].push_back({{x, 0}, graph[x].size() - 1});

    }

    for (int i = 1; i <= n; i++) {
        graph[start].push_back({{i, 1}, graph[i].size()});
        graph[i].push_back({{start, 0}, graph[start].size() - 1});
    }

    for (int i = 1; i <= m; i++) {
        graph[i + n].push_back({{final, 1}, graph[final].size()});
        graph[final].push_back({{i + n, 0}, graph[i + n].size() - 1});
    }

    int maxFlow = EdK();
    out << maxFlow << '\n';

//    muchiile din prima in a doua grupa care au capacitatea saturata
    for (int node1 = 1; node1 <= n; node1++)
        for (int j = 0; j < graph[node1].size(); j++) {
            int node2, capacity;
            node2 = graph[node1][j].first.first;
            capacity = graph[node1][j].first.second;
            if (node2 != 0 && capacity != 1)
                out << node1 << " " << node2 - n << '\n';
        }
    return 0;
}