#include <bits/stdc++.h>

using namespace std;

ifstream in("bellmanford.in");
ofstream out("bellmanford.out");

vector<pair<int, int>> *graph;
vector<int> dist;
vector<int> in_q;
vector<int> nr;
queue<int> q;
int n, m;

// Bellman-Ford
int BellmanFord(int node) {
    q.push(node);
    dist[node] = 0;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        in_q[node] = 0;

        for (auto neigh: graph[node]) {
            int next = neigh.first;
            int cost = neigh.second;

            if (dist[node] + cost < dist[next]) {
                dist[next] = dist[node] + cost;

                nr[next]++;
                if (nr[next] > n + 1)
                    return 0;

                if (!in_q[next]) {
                    q.push(next);
                    in_q[next] = 1;
                }
            }
        }
    }
    return 1;
}

int main() {

    in >> n >> m;

    graph = new vector<pair<int, int>>[50001];
    dist.resize(50001, INT_MAX);
    in_q.resize(50001);
    nr.resize(50001);

    for (int i = 1; i <= m; i++) {
        int x, y, c;
        in >> x >> y >> c;
        graph[x].emplace_back(y, c);
    }

    if (!BellmanFord(1))
        out << "Ciclu negativ!\n";
    else {
        for (int i = 2; i <= n; i++)
            if (dist[i] == INT_MAX)
                out << 0 << ' ';
            else
                out << dist[i] << ' ';
    }

    in.close();
    out.close();
    return 0;
}