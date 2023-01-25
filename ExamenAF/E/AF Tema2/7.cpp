//construim un graf complet dat de punctele din cerinta
//Algoritmul lui Kruskal - arbore partial de cost minim

#include <bits/stdc++.h>
using namespace std;

ifstream in("graf.in");

vector<pair<int, pair<int, int>>> g;
vector<int> tata, r;
int n;

void Init(){
    for (int i = 1; i <= n; ++i){
        tata[i] = i;
        r[i] = 1;
    }
}

int Find(int nod){
    while (tata[nod] != nod)
        nod = tata[nod];
    return tata[nod];
}


// reuniune ponderata
// radacina unui arbore devine fiu al radacinii celuilalt arbore
// arborele cu inaltimea mai mica devine subarbore al radacinii celuilalt arbore

void Union(int x, int y){
    if (r[x] < r[y])
        tata[x] = y;
    if (r[x] > r[y])
        tata[y] = x;
    if (r[x] == r[y]){
        tata[x] = y;
        r[y]++;
    }
}

int main(){
    vector<vector<int>> points = {{3, 12}, {-2, 5}, {-4, 1}};
    n = points.size();
    tata.resize(n+1);
    r.resize(n+1);

    Init();

    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){

            //manhattan distance
            int cost = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);

            g.push_back({cost, {i, j}});

        }
    }

    // sort on edge cost (first element in pair)
    sort(g.begin(), g.end());

    int sum = 0;

    // for each edge we travel
    for(int i = 0; i < g.size(); i++)   {

        int a = Find(g[i].second.first); // first node
        int b = Find(g[i].second.second); // second node

        if(a != b){ // if both parents are not same then add cost
            sum += g[i].first;
            Union(a, b); // now merge them
        }
    }

    cout<<sum;
}
