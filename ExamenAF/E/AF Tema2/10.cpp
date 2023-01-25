#include <bits/stdc++.h>
using namespace std;

ifstream in("apm2.in");
ofstream out("apm2.out");

vector<pair<int, pair<int, int>>> g;
vector<pair<int, int>> g2;
vector<int> tata, r, rez;
int n, m, q;

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

int main() {
    in >> n >> m >> q;

    r.resize(n+1);
    tata.resize(n+1);
    rez.resize(q+1);

    for (int i = 0; i < m; i++){
        int x, y, cost;
        in >> x >> y >> cost;
        g.push_back({cost, {x, y}});
    }

    //sortam muchiile dupa cost
    sort(g.begin(), g.end());

    //citim drumurile care urmeaza sa fie adaugate
    for (int i = 0; i < q; i++){
        int x, y, cost;
        in >> x >> y ;
        g2.push_back({x, y});
    }

    //configuram pt kruskal
    Init();

    //kruskal propriu zis
    for (int i = 0; i < m; i++) {
        if (g[i].first != g[i - 1].first)
            //verificam pt noile muchii
            for (int j = 0; j < q; j++)
                if (Find(g2[j].first) != Find(g2[j].second))
                    rez[j] = g[i].first - 1;

        if (Find(g[i].second.first) != Find(g[i].second.second))
            Union(Find(g[i].second.first), Find(g[i].second.second));
    }

    for (int i = 0; i < q; ++i)
        out << rez[i] << '\n';
    return 0;
}