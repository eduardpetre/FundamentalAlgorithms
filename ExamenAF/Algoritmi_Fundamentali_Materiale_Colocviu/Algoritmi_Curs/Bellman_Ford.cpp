#include <bits/stdc++.h>
using namespace std;
ifstream f("graf.in");
int n,m;
vector<vector<pair<int, int>>> graph;
queue<int> q;
vector<int> dist, father, in_q;

void bellmand_ford(int start){
    dist[start]=0;
    father[start]=0;
    q.push(start);

    in_q[start]=1;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        in_q[u]=0;
        for(int i=0;i<graph[u].size();i++){
            int v=graph[u][i].first;
            int cost=graph[u][i].second;
            if(dist[u]<INT_MAX && dist[u] + cost < dist[v]){
                dist[v]= dist[u] + cost;
                father[v]=u;
                if(in_q[v]==0){
                    q.push(v);
                    in_q[v]=1;
                }
            }

        }
    }
}


int main() {

    f>>n>>m;
    graph.resize(n+1);
    father.resize(n+1);
    dist.resize(n+1);
    in_q.resize(n+1);
    for(int i=1;i<=n;i++){
        dist[i]=INT_MAX;
    }
    for(int i=0;i<m;i++){
        int x,y,cost;
        f>>x>>y>>cost;
        graph[x].push_back({y,cost});
    }

    int start_node, target_node;
    cout<<"Nodul de start este:\n";
    cin>>start_node;
    bellmand_ford(start_node);
    cout<<"\nNodul destinatie:\n";
    cin>>target_node;
    cout<<target_node;
    while(father[target_node]!=0){
        cout<<" -> "<<father[target_node];
        target_node=father[target_node];
    }

    return 0;
}
