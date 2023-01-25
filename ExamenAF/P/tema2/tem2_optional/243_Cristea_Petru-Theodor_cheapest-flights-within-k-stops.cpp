#include <bits/stdc++.h>
using namespace std;

ifstream fin("graf.in");

//vector<vector<int>> graf;
vector<pair<int, pair<int, int>>> graf;
vector<int> parinte;


int main(){
    int n = 3, src = 0, dst = 2, k = 0;
    vector<vector<int>> flights = {{0,1,100}, {1,2,100}, {0,2,500}};

    vector<pair<int, int>> muchii[n];
        vector<int> distanta(n, 1e9);
        queue<vector<int>> q;

        for(auto it: flights){
            muchii[it[0]].push_back({it[1], it[2]});
        }

        // primul nod (sursa) in coada
        q.push({0, src, 0});
        // distanta de la sursa la sursa e 0
        distanta[src] = 0;

        while(!q.empty()){
            // lucram cu primul element din coada
            int stop = q.front()[0];
            int node = q.front()[1];
            int cost = q.front()[2];
            // eliminam nodul pe care il folosim din coada
            q.pop();

            // ne oprim daca atingem k stopuri
            if(stop > k) continue;

            // pt nodul curent vizitam muchiile adiacente
            for(auto it: muchii[node]){
                int nod1 = it.first;
                int weight = it.second;

                if(cost + weight < distanta[nod1]) {
                    distanta[nod1] = cost + weight;  // actualizam distanta
                    q.push({stop+1, nod1, cost + weight});  // punem nodul adiacent si noua distanta in coada
                }
            }
        }

        // afisam -1 daca nu putem ajunge
        if(distanta[dst] == 1e9)
            cout<<-1;
        else cout << distanta[dst];
    }
