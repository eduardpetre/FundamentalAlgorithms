#include <bits/stdc++.h>
using namespace std;
ifstream f("graf.in");
int n, m;
vector<vector<int>> graph;
vector<vector<int>> graph_t;
vector<int>viz;
stack<int> st;
vector<int> componenta;
vector<vector<int>> componente_tari;

void dfs(int node){
    viz[node]=1;
    for(int i=0;i<graph[node].size();i++){
        if(viz[graph[node][i]]==0){
            dfs(graph[node][i]);

        }
    }
    st.push(node);
}

void dfs_t(int node){
    componenta.push_back(node);
    viz[node]=1;
    for(int i=0;i<graph_t[node].size();i++){
        if(viz[graph_t[node][i]]==0){
            dfs_t(graph_t[node][i]);

        }
    }
}

int main() {

    f>>n>>m;
    graph.resize(n+1);
    graph_t.resize(n+1);
    viz.resize(n+1);
    for(int i=0;i<m;i++){
        int x,y;
        f>>x>>y;
        graph[x].push_back(y);
        graph_t[y].push_back(x);
    }
    for(int i=1;i<=n;i++){
        if(viz[i]==0){
            dfs(i);
        }
    }
    for(int i=1;i<=n;i++){
        viz[i]=0;
    }

    while(!st.empty()){
        int node=st.top();
        st.pop();
        if(viz[node]==0){
            dfs_t(node);
            componente_tari.push_back(componenta);
            componenta.clear();
        }

    }

    for (int i = 1; i <= n; ++i) {
        if (!viz[i]) {
            dfs_t(i);
            componente_tari.push_back(componenta);
            componenta.clear();
        }
    }

    cout <<"Componente tari conexe gasite - "<< componente_tari.size()<<":";
    for (auto &comp : componente_tari) {
        cout << '\n';
        for (auto &i : comp)
            cout << i << ' ';
    }


    return 0;
}
