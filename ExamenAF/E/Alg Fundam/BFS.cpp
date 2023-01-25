#include <bits/stdc++.h>

using namespace std;

ifstream in("bfs.in");
ofstream out("bfs.out");

int n, m, s;
vector<vector<int>> graph;
vector<int> dist;
vector<bool> visited;
queue<int> q;

void bfs(int s) {
    q.push(s);
    visited[s] = true;
    dist[s] = 0;
    cout<<s<<" ";
    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (auto neigh: graph[node]){
            if (!visited[neigh]) {
                cout<<neigh<<" ";
                q.push(neigh);
                visited[neigh] = true;
                dist[neigh] = dist[node] + 1;
            }
        }
    }
}

int main() {
    in >> n >> m >> s;

    graph.resize(n + 1);
    visited.resize(n + 1);
    dist.resize(n + 1, -1);

    for (int i = 0; i < m; i++) {
        int x, y;
        in >> x >> y;

        graph[x].push_back(y);
    }

    bfs(s);

    for (int i = 1; i <= n; i++)
        out << dist[i] << " ";

    in.close();
    out.close();
    return 0;
}
