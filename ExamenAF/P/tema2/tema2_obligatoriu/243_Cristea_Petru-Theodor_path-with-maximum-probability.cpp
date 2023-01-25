#include <bits/stdc++.h>

using namespace std;

ifstream fin("graf.in");
//ofstream fout("catun.out");

int ans[36001];
int minim[36001];
vector<pair<int, float>> graf[36001];   //perechi sa tinem distanta

double dijkstra() {
    int n = 3, start=0, stop=2;

    priority_queue<pair<double,int>> p;
    vector<double> dist(n,0.0);

    p.push({1.0,start});

    dist[start]=1.0;

    while(!p.empty()){
        double cost=p.top().first;
        int node=p.top().second;

        p.pop();
        for(auto it:graf[node]){
            if(dist[it.first]<it.second*cost){
                dist[it.first]=it.second*cost;
                p.push({dist[it.first],it.first});
            }
        }
    }
    return dist[dist.size()-1];
}

int main() {

    while(!fin.eof()) {
        int x, y; float z;
        fin >> x >> y >> z;
        graf[x].push_back({y, z});  //distanta de la x la y este z
        graf[y].push_back({x, z});  //distanta de la y la x este z
    }

    cout<<dijkstra();
}


/*
LEETCODE

class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {

    vector<pair<int, float>> graf[100000];

    for(int i=0;i<edges.size();i++){
            int u=edges[i][0];
            int v=edges[i][1];
            graf[u].push_back({v,succProb[i]});
            graf[v].push_back({u,succProb[i]});
        }

    priority_queue<pair<double,int>> p;
    vector<double> dist(n,0.0);

    p.push({1.0,start});

    dist[start]=1.0;

    while(!p.empty()){
        double cost=p.top().first;
        int node=p.top().second;

        p.pop();
        for(auto it:graf[node]){
            if(dist[it.first]<it.second*cost){
                dist[it.first]=it.second*cost;
                p.push({dist[it.first],it.first});
            }
        }
    }
    return dist[end];
    }
};
/*
