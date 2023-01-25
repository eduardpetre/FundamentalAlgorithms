#include <bits/stdc++.h>
using namespace std;
ifstream f("graf.in");
vector<vector<int>> graph;
vector<int> desc, fin, viz, father, level, color;
int n,m,timer;
vector<pair<int, int>> edges, return_edges;
vector<vector<int>> cycles;

void init(){

    desc.resize(n+2,0);
    viz.resize(n+2,0);
    father.resize(n+2,0);
    fin.resize(n+2,0);
    level.resize(n+2,0);
    color.resize(n+2,0);
}


void dfs(int x){
    timer++;
    desc[x]=timer;
    color[x]=1;

    for(int i=0;i<graph[x].size();i++){
        if(color[graph[x][i]] == 0 ){
            father[graph[x][i]]=x;
            level[graph[x][i]]=level[x]+1;
            dfs(graph[x][i]);

        }else{
            if(father[x]!=graph[x][i] && color[graph[x][i]]==1){
                return_edges.emplace_back(x, graph[x][i]);
                int v = x;
                vector<int> cycle;
                while (v != graph[x][i]) {
                    cycle.push_back(v);
                    v=father[v];
                }
                cycle.push_back(graph[x][i]);
                cycle.push_back(x);
                cycles.push_back(cycle);
            }

        }
    }
    color[x]=2;
    timer++;
    fin[x]=timer;
}




int main() {

    f>>n>>m;
    graph.resize(n+2);
    init();
    for(int i=0;i<m;i++){
        int x,y;
        f>>x>>y;
        edges.emplace_back(x,y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }


    // afisez muchiile de intoarcere
    for(int i=1;i<=n;i++){
        if(color[i]==0){
            dfs(i);
        }
    }
    cout<<"Muchiile de intoarcere sunt:\n";
    for(int i=0;i<return_edges.size();i++){
        cout<<return_edges[i].first<<" - "<<return_edges[i].second<<"\n";
    }
    cout<<"\n\nCiclurile in acest graf sunt:\n";
    for(int i=0;i<cycles.size();i++){
        for(int j=0;j<cycles[i].size();j++){
            cout<<cycles[i][j]<<"   ";
        }
        cout<<"\n";
    }
    return 0;
}
