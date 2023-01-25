#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> *g;
vector<int> distanta;
queue<vector<int>> q;

int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {

    g = new vector <pair <int, int>> [n + 1];
    distanta.resize(n+1, INT_MAX);

    for(auto it: flights){
        g[it[0]].emplace_back(it[1], it[2]);
    }

    // primul nod (sursa) in coada
    q.push({0, src, 0});
    // distanta de la sursa la sursa e 0
    distanta[src] = 0;

    while(!q.empty()){
        int stop = q.front()[0];
        int node = q.front()[1];
        int dist = q.front()[2];
        q.pop();

        // ne oprim daca atingem k stopuri
        if (stop > k)
            continue;

        // pt nodul curent vizitam muchiile adiacente
        for(auto it: g[node]){
            int vecin = it.first;
            int cost = it.second;

            if(dist + cost < distanta[vecin]) {
                distanta[vecin] = dist + cost;
                q.push({stop+1, vecin, dist + cost});
            }
        }
    }

    if(distanta[dst] == INT_MAX)
        return -1;
    else
        return distanta[dst];
}

int main(){
    int n = 3, src = 0, dst = 2, k = 0;
    vector<vector<int>> flights = {{0,1,100}, {1,2,100}, {0,2,500}};

    cout<<findCheapestPrice(n, flights, src, dst, k);

    return 0;
}