#include <bits/stdc++.h>
using namespace std;
ifstream f("graf.in");
int n, m;
queue<int> coada;
vector<int> grade_intrare;
vector<int> sortare;
vector<vector<int>> graph;


int main() {

    f>>n>>m;
    graph.resize(n+2);
    grade_intrare.resize(n+2);
    for(int i=0;i<m;i++){
        int x,y;
        f>>x>>y;
        grade_intrare[y]++;
        graph[x].push_back(y);


    }
    for(int i=1;i<=n;i++){
        if(grade_intrare[i]==0){
            coada.push(i);
        }
    }
    while(!coada.empty()){
        int node=coada.front();
        coada.pop();
        sortare.push_back(node);
        for(int i=0;i<graph[node].size();i++){
            grade_intrare[graph[node][i]]=grade_intrare[graph[node][i]]-1;
            if(grade_intrare[graph[node][i]]==0){
                coada.push(graph[node][i]);
            }
        }
    }

    for(int i=0;i<sortare.size();i++){
        cout<<sortare[i]<<" ";
    }
    return 0;
}
