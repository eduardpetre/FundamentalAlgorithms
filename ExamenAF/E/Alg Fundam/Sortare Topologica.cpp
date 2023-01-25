#include <bits/stdc++.h>

using namespace std;

ifstream in("sortaret.in");
ofstream out("sortaret.out");

int n, m;
vector<vector<int>> graph;
vector<bool> visited;
vector<int> degreein;
vector<int> tsort;

void dfs(int s) {
    tsort.push_back(s);

    visited[s] = true;

    for (auto neigh: graph[s]) {
        degreein[neigh]--;
        if (!visited[neigh] && !degreein[neigh])
            dfs(neigh);
    }
}

int main() {
    in >> n >> m;

    graph.resize(n + 1);
    visited.resize(n + 1);
    degreein.resize(n+1);

    for (int i = 0; i < m; i++) {
        int x, y;
        in >> x >> y;

        degreein[y]++;
        graph[x].push_back(y);
    }

    for (int i = 1; i <= n; i++)
        if(!visited[i] && !degreein[i])
            dfs(i);

    for(auto x:tsort)
        out<<x<<" ";

    in.close();
    out.close();
    return 0;
}