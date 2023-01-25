// Algoritmul lui Kruskal pe primele n orase si apoi pe fiecare dintre cele k

#include<bits/stdc++.h>
using namespace std;

ifstream in("online.in");
ofstream out("online.out");

vector<pair<int, pair<int, int>>> g;
vector<int> tata, r;
int n,m;

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

int kruskal(){

    Init();

    sort(g.begin(), g.end());

    int s = 0;
    vector<pair<int, pair<int, int>>> apm;

    for (int i = 0; i < (int)g.size(); i++){

        int a = Find(g[i].second.first);
        int b = Find(g[i].second.second);

        if (a != b){
            Union(a, b);
            s+=g[i].first;
            apm.push_back(g[i]);
        }
    }
    g = apm;
    return s;
}


int main(){
    in >> n >> m;

    tata.resize(n+1);
    r.resize(n+1);

    for (int i = 1; i <= m; i++){
        int x, y, cost;
        in >> x >> y >> cost;
        g.push_back({cost, {x, y}});
    }

    out<<kruskal()<<endl;

    int k;
    in>>k;
    for(int i = 0; i < k; i++){
        int x, y, cost;
        in >> x >> y >> cost;
        g.push_back({cost, {x, y}});

        out<<kruskal()<<endl;
    }

    return 0;
}