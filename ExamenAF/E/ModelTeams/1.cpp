#include <bits/stdc++.h>

using namespace std;

ifstream in("sub1.in");
ofstream out("sub1.out");

int n, m, s;

vector<vector<int>> graf;
vector<vector<int>> comp_conexe;
vector<int> visited, cc;

void dfs(int s) {
    visited[s] = 1;

    cc.push_back(s);

    for (auto &vecin: graf[s]) {
        if (!visited[vecin]) {
            dfs(vecin);
        }
    }
}


queue<int> q;
vector<int> dist;

void bfs(int s) {
    q.push(s);
    visited[s] = true;
    dist[s] = 0;
    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (auto neigh: graf[node]) {
            if (!visited[neigh]) {
                q.push(neigh);
                visited[neigh] = true;
                dist[neigh] = dist[node] + 1;
            }
        }
    }
}

int main() {
    in >> n >> m;

    graf.resize(n + 1);
    visited.resize(n + 1, 0);

    for (int i = 0; i < m; i++) {
        int x, y;
        in >> x >> y;

        graf[x].push_back(y);
        graf[y].push_back(x);
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
        if (!cc.empty())
            comp_conexe.push_back(cc);
        cc.clear();
    }

    for (int i = 0; i < comp_conexe.size() - 1; i++) {
        int a = comp_conexe[i][0];
        int b = comp_conexe[i + 1][0];

        graf[a].push_back(b);
        graf[b].push_back(a);

        cout << a << " " << b << endl;
    }
    cout << endl;

    visited.assign(n + 1, false);
    dist.resize(n + 1);

    in >> s;
    bfs(s);
    int maxi = 0;

    for (int i = 1; i <= n; i++)
        maxi = max(maxi, dist[i]);
    cout << maxi;

    return 0;
}