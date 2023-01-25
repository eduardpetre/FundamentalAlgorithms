#include <bits/stdc++.h>
using namespace std;
ifstream f("graf.in");

vector<vector<int>> graph;
vector<int> desc, fin, viz, father, level, color;
int n, m, timer;
vector<pair<int,int>> all_edges;
vector<vector<int>> circuits;


// tipuri de arce

vector<pair<int,int>> arce_avansare_directa;
vector<pair<int,int>> arce_avansare_inainte;
vector<pair<int,int>> arce_intoarcere;
vector<pair<int,int>> arce_traversare;

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
            arce_avansare_directa.push_back({x, graph[x][i]});
            father[graph[x][i]]=x;
            level[graph[x][i]]=level[x]+1;
            dfs(graph[x][i]);


        }else{
            if(color[graph[x][i]]==2 && desc[x] < desc[graph[x][i]]){
                arce_avansare_inainte.push_back({x, graph[x][i]});
            }
            if(color[graph[x][i]]==1){
                arce_intoarcere.push_back({x, graph[x][i]});
            }
            if(color[graph[x][i]]==2 && desc[x]>desc[graph[x][i]]){
                arce_traversare.push_back({x, graph[x][i]});
            }
            if(fin[graph[x][i]]==0){
                int v=x;
                vector<int> circuit;
                while(v!=graph[x][i]){
                    circuit.push_back(v);
                    v=father[v];
                }
                circuit.push_back(graph[x][i]);
                circuit.push_back(x);
                reverse(circuit.begin(), circuit.end());
                circuits.push_back(circuit);
            }

        }
    }
    color[x]=2;
    timer++;
    fin[x]=timer;
}



int main() {

    f>>n>>m;
    init();
    graph.resize(n+2);
    for(int i=0;i<m;i++){
        int x,y;
        f>>x>>y;
        graph[x].push_back(y);
        all_edges.push_back({x,y});
    }
    for(int i=1;i<=n;i++){
        if(color[i]==0){
            dfs(i);
        }
    }

    cout<<"Arce de avansare inainte:\n";
    for(int i=0;i<arce_avansare_inainte.size();i++){
        cout<<arce_avansare_inainte[i].first<<" -> "<<arce_avansare_inainte[i].second<<"\n";
    }

    cout<<"\n\nArce de intoarcere:\n";
    for(int i=0;i<arce_intoarcere.size();i++){
        cout<<arce_intoarcere[i].first<<" -> "<<arce_intoarcere[i].second<<"\n";
    }

    cout<<"\n\nArce de traversare:\n";
    for(int i=0;i<arce_traversare.size();i++){
        cout<<arce_traversare[i].first<<" -> "<<arce_traversare[i].second<<"\n";
    }

    cout<<"\n\nArce de avansare directa:\n";
    for(int i=0;i<arce_avansare_directa.size();i++){
        cout<<arce_avansare_directa[i].first<<" -> "<<arce_avansare_directa[i].second<<"\n";
    }

    cout<<"\n\nCircuitele sunt:\n";
    for(int i=0;i<circuits.size();i++){
        for(int j=0;j<circuits[i].size();j++){
            cout<<circuits[i][j]<<" ";
        }
        cout<<"\n";
    }
    return 0;
}
