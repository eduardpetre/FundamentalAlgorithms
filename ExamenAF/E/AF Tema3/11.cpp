#include <bits/stdc++.h>
using namespace std;

ifstream in("johnie.in");
ofstream out("johnie.out");

int n, m, nr;
unordered_map<int, vector<pair<int, int>>> edges(50001);
unordered_map<int, int> degree;
unordered_map<int, vector<int>> ans;
vector<bool> visited(1000001);

void dfs(int node) {
    int nodeNeigh, edgeNeigh;
    while (!edges[node].empty()) {
        auto edge = edges[node].back();
        nodeNeigh = edge.first;
        edgeNeigh = edge.second;

        edges[node].pop_back();

        if (!visited[edgeNeigh]) {
            visited[edgeNeigh] = true;
            dfs(nodeNeigh);
        }
    }

    if (node == 0)
        nr++;
    else ans[nr].push_back(node);
}


int main() {

    in >> n >> m;

    int x, y;
    for (int i = 0; i < m; i++) {
        in >> x >> y;

        edges[x].push_back({y, i});
        edges[y].push_back({x, i});

        degree[x] += 1;
        degree[y] += 1;
    }

    for (int node = 1; node <= n; node++)
        if (degree[node] % 2) {
            edges[node].push_back({0, node + m});
            edges[0].push_back({node, node + m});
        }

    dfs(0);

    out << ans.size() << endl;
    for (auto step: ans) {
        out << step.second.size() << " ";
        for (auto node: step.second)
            out << node << " ";
        out << "\n";
    }

    return 0;
}