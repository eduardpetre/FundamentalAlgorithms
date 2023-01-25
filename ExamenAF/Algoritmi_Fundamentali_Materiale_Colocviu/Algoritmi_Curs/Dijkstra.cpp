#include <bits/stdc++.h>
using namespace std;
ifstream f("graf.in");
int n, m;
vector<int> minim, result;
vector<vector<pair<int, int>>> graph;
priority_queue<pair<int, int>> q;

void dijkstra(int node){
    q.push({0, node});
    while(!q.empty()){
        int nod=q.top().second;
        q.pop();
        for(auto&v : graph[nod]){
            if(minim[nod]+v.second < minim[v.first]){
                minim[v.first]=minim[nod]+v.second;
                q.push(make_pair(-minim[v.first], v.first ));
                result[v.first] = nod;
            }

        }
    }
}

int main() {

    f>>n>>m;
    minim.resize(n+1);
    graph.resize(n+1);
    result.resize(n+1);
    for(int i=0;i<m;i++){
        minim[i]=INT_MAX;
    }
    for(int i=0;i<m;i++){
        int x,y,cost;
        f>>x>>y>>cost;
        graph[x].push_back(make_pair(y, cost));

    }




    int start_node, target_node;
    cout<<"Selectati un nod de start:\n";
    cin>>start_node;
    dijkstra(start_node);
    cout<<"Selectati nodul destinatie:\n";
    cin>>target_node;

    cout<<"\nTraseul de intoarcere este:\n"<<target_node<<" ";
    while(result[target_node]!=0){
        cout<<" -> "<<result[target_node];
        target_node=result[target_node];
    }


    return 0;
}
