#include <bits/stdc++.h>

using namespace std;

ifstream in("dfs.in");
ofstream out("dfs.out");

int n, m;
vector<vector<int>> graph;
vector<bool> visited;
int ok;

void dfs(int s) {
    if (!visited[s])
        ok = 1;

    visited[s] = true;

    cout << s << " ";

    for (auto neigh: graph[s]) {
        if (!visited[neigh]) {
            dfs(neigh);
        }
    }
}

int main() {
    in >> n >> m;

    graph.resize(n + 1);
    visited.resize(n + 1);

    for (int i = 0; i < m; i++) {
        int x, y;
        in >> x >> y;

        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    int nrcomp = 0;
    for (int i = 1; i <= n; i++) {
        dfs(i);
        if (ok == 1)
            nrcomp++;
        ok = 0;
    }

    out << nrcomp;

    in.close();
    out.close();
    return 0;
}