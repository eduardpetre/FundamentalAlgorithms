#include <bits/stdc++.h>
using namespace std;
ifstream f("graf.in");
int n,m;
vector<vector<int>>graph;
vector<int> color;
bool dfs(int x, int color_index){
    color[x]=color_index;
    for(int i=0;i<graph[x].size();i++){
        if(color[graph[x][i]]==color_index){
            return false;
        }
        if(color[graph[x][i]]==0 && !dfs(graph[x][i], -color_index)){
            return false;
        }
    }
    return true;
}

int main() {

    f>>n>>m;
    graph.resize(n+2);
    color.resize(n+2);
    for(int i=0;i<m;i++){
        int x,y;
        f>>x>>y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    if(!dfs(1, 1)){
        cout<<"Nu e bipartit";
    }else{
        cout<<"Este bipartit";
    }

    return 0;
}
