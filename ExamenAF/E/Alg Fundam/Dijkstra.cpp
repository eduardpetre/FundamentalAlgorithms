#include <bits/stdc++.h>

using namespace std;

ifstream in("dijkstra.in");
ofstream out("dijkstra.out");

vector<pair<int, int>> *graph;
vector<int> dist;
vector<int> visited;
priority_queue<pair<int, int>> q;

int n, m;

// Dijkstra Algorithm
void Dijsktra(int start) {
    q.emplace(0, start);
    dist[start] = 0;

    while (!q.empty()) {
        int node = q.top().second;
        q.pop();

        if (!visited[node]) {
            visited[node] = 1;

            for (auto neigh: graph[node]) {
                int next = neigh.first;
                int cost = neigh.second;
                if (dist[node] + cost < dist[next]) {
                    dist[next] = dist[node] + cost;
                    q.emplace(-dist[next], next);
                }
            }
        }
    }
}

int main() {
    in >> n >> m;
    graph = new vector <pair <int, int>> [50001];
    visited.resize(50001, 0);
    dist.resize(50001, INT_MAX);

    for (int i = 0; i < m; i++) {
        int x, y, c;
        in >> x >> y >> c;
        graph[x].emplace_back(make_pair(y, c));
    }

    Dijsktra(1);

    for (int i = 2; i <= n; i++) {
        if (dist[i] == INT_MAX)
            out << 0 << ' ';
        else
            out << dist[i] << ' ';
    }

    in.close();
    out.close();
    return 0;
}