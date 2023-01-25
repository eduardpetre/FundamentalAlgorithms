#include <bits/stdc++.h>
using namespace std;

ifstream in("graf.in");
vector<vector<int>> graph;
vector<bool> visited;
vector<int> disc, low; // discovery time, lowest future node
int timer;
int n;


//Tarjan's Algorithm
void dfs(int curr, int prev = -1) {
    visited[curr] = true;
    disc[curr] = low[curr] = timer++;

    cout<<curr<<", "<<prev<<": ";
    for (int next : graph[curr]) {
        cout<<next<<" ";
        if(next == prev)
            continue;

        if (visited[next])
            low[curr] = min(low[curr], disc[next]);

        else{
            dfs(next, curr);
            low[curr] = min(low[curr], low[next]);

            if (low[next] > disc[curr])
                cout<<curr<<' '<<next<<endl;
        }
        cout<<endl;
    }
}

int main(){
    in >> n;
    graph.resize(n);
    while(!in.eof()){
        int nod1, nod2;
        in>>nod1>>nod2;
        graph[nod1].push_back(nod2);
        graph[nod2].push_back(nod1);
    }

    visited.assign(n, false);
    disc.assign(n, -1);
    low.assign(n, -1);

    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs(i);
    }

    return 0;
}

