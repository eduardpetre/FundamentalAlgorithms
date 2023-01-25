#include <bits/stdc++.h>

using namespace std;

ifstream in("sub3.in");
ofstream out("sub3.out");

int n, m, p, start, final;

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

    in >> n >> m >> p;

    start = 0;
    final = n + 1;

    graph.resize(final + 1);
    parent.resize(final + 1);
    visited.resize(final + 1);

    for (int i = 0; i < m; i++) {
        int x, y;
        in >> x >> y;

        graph[x].push_back({{y, 1}, graph[y].size()});
        graph[y].push_back({{x, 0}, graph[x].size() - 1});
    }

    for (int i = 1; i <= p; i++) {
        graph[start].push_back({{i, 1}, graph[i].size()});
        graph[i].push_back({{start, 0}, graph[start].size() - 1});
    }

    for (int i = p+1; i <= n; i++) {
        graph[i].push_back({{final, 1}, graph[final].size()});
        graph[final].push_back({{i, 0}, graph[i].size() - 1});
    }

    int maxFlow = EdK();

//    muchiile din prima in a doua grupa care au capacitatea saturata
    int k, ok = 0;
    cin>>k;
    if (maxFlow < k)
        cout<<"Nu exista!";
    else {
        for (int node1 = 1; node1 <= p; node1++)
            for (int j = 0; j < graph[node1].size(); j++) {
                int node2, capacity;
                node2 = graph[node1][j].first.first;
                capacity = graph[node1][j].first.second;
                if (node2 != start && capacity != 1 && ok<k) {
                    out << node1 << " " << node2 << '\n';
                    ok++;
                }
            }
    }

    vector<int> degree;
    degree.resize(final + 1, 0);
    for (int node1 = 1; node1 <= p; node1++)
        for (int j = 0; j < graph[node1].size(); j++) {
            int node2 = graph[node1][j].first.first;
            if (degree[node1] < 2 && degree[node2] < 2) {
                cout << node1 << " " << node2<<endl;
                degree[node1]++;
                degree[node2]++;
            }
        }

    return 0;
}