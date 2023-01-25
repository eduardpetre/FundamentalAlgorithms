#include <bits/stdc++.h>

using namespace std;
ifstream fin("johnie.in");
ofstream fout("johnie.out");

int n, m, x, y, nr;
unordered_map <int, vector <pair <int, int>>> graf(50001);
unordered_map <int, int> grad;
unordered_map <int, vector <int>> ans;
vector <bool> muchii_vizitate(1000001);

// calculez gradul pentru fiecare nod
// daca gradul unui nod este impar, atunci creez o muchie de la nodul S la node
// aplic un DFS verificand daca am trecut prin muchie

void dfs (int nod_curent){
    while (!graf[nod_curent].empty()) {
        auto pereche_vecina = graf[nod_curent].back();
        int nod_vecin = pereche_vecina.first;
        int muchie_vecina = pereche_vecina.second;

        graf[nod_curent].pop_back();

        if (muchii_vizitate[muchie_vecina] == false) {
            muchii_vizitate[muchie_vecina] = true;
            dfs(nod_vecin);
        }
    }

    if (nod_curent == 0)
        nr++;
    else ans[nr].push_back(nod_curent);
}


int main()
{
    fin >> n >> m;

    for (int i=0; i<m; i++){
        fin >> x >> y;

        graf[x].push_back({y, i});
        graf[y].push_back({x, i});

        grad[x] += 1;
        grad[y] += 1;
    }

    for (int nod=1; nod<=n; nod++)
        if (grad[nod]%2){
            graf[nod].push_back({0, nod + m});
            graf[0].push_back({nod, nod + m});
        }

    dfs(0);

    fout << ans.size() << endl;
    for (auto etapa : ans){
       fout << etapa.second.size() << " ";
        for (auto nod : etapa.second)
           fout << nod << " ";
        fout << '\n';
    }
    return 0;
}

