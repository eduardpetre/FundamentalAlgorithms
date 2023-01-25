#include <bits/stdc++.h>
using namespace std;
ifstream f("graf.in");
int n,m;
vector<vector<int>> graph;
vector<int> father, height;
vector<tuple<int, int, int>> edges;
vector<tuple<int, int, int>> edges_apm;
int final_cost;

bool cmp(tuple<int, int, int> edge_one, tuple<int, int, int> edge_two){
    return get<2>(edge_one) < get<2>(edge_two);
}

void initializare(int x){
    father[x]=0;
    height[x]=0;
}

int reprezentant(int u){
    while(father[u]!=0){
        u=father[u];
    }
    return u;
}

void reuneste(int u, int v){
    int ru, rv;
    ru= reprezentant(u);
    rv= reprezentant(v);
    if(height[ru]>height[rv]){
        father[rv]=ru;
    }else{
        father[ru]=rv;
        if(height[ru]==height[rv]){
            height[rv]=height[rv]+1;
        }
    }
}

int main() {
    f>>n>>m;
    graph.resize(n+2);
    father.resize(n+2);
    height.resize(n+2);
    for(int i=1;i<=m;i++){
        int x,y, cost;
        f>>x>>y>>cost;
        graph[x].push_back(y);
        graph[y].push_back(x);
        tuple<int, int, int> edge;
        edge = {x, y, cost};
        edges.push_back(edge);
    }
    sort(edges.begin(), edges.end(), cmp);
    for(int i=1;i<=n;i++){
        initializare(i);
    }
    for(int i=0;i<m;i++){
        if(reprezentant(get<0>(edges[i])) == reprezentant(get<1>(edges[i]))){
            continue;
        }
        reuneste(get<0>(edges[i]), get<1>(edges[i]));
        edges_apm.push_back(edges[i]);
        final_cost+=get<2>(edges[i]);
    }
    cout<<"Costul final este: "<<final_cost<<"\n";
    cout<<"Muchiile din apm sunt:\n";
    for(int i=0;i<edges_apm.size();i++){
        cout<<"Muchia "<<get<0>(edges_apm[i])<<" - "<<get<1>(edges_apm[i])<<" cu costul "<<get<2>(edges_apm[i])<<"\n";
    }

    return 0;
}
