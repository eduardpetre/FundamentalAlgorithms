#include <bits/stdc++.h>

using namespace std;

ifstream in("sub1.in");
ofstream out("sub1.out");

int n, m, s;
vector<vector<int>> graph;
vector<int> dist1;
vector<int> dist2;
vector<bool> visited;
queue<int> q;

void bfs(int s) {
    q.push(s);
    visited[s] = true;
    dist1[s] = 0;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (auto neigh: graph[node]){
            if (!visited[neigh]) {
                cout<<node<<" "<<neigh<<endl;
                q.push(neigh);
                visited[neigh] = true;
                dist1[neigh] = dist1[node] + 1;
            }
        }
    }
}

void dfs(int s) {
    visited[s] = true;

    for (auto neigh: graph[s]) {
        if (!visited[neigh]) {
            cout<<s<<" "<<neigh<<endl;
            dist2[neigh] = dist2[s] + 1;
            dfs(neigh);
        }
    }
}

int main() {
    in >> n >> m;

    graph.resize(n + 1);
    visited.resize(n + 1);
    dist1.resize(n + 1, -1);
    dist2.resize(n + 1, -1);

    for (int i = 0; i < m; i++) {
        int x, y;
        in >> x >> y;

        graph[x].push_back(y);
    }

    in>>s;
    bfs(s);
    cout<<endl;

    visited.assign(n + 1, false);
    dist2[s] = 0;
    dfs(s);
    cout<<endl;

    for (int i = 1; i <= n; i++)
        if(dist1[i]!=dist2[i]) {
            cout << "u = " << i;
            break;
        }
    cout<<endl<<endl;

    for (int i = 1; i <= n; i++)
        cout<<dist1[i]<<" ";
    cout<<endl;

    for (int i = 1; i <= n; i++)
        cout<<dist2[i]<<" ";

    in.close();
    out.close();
    return 0;
}
