// Algoritmul lui Dijkstra shortest path cu ajutorul unui min heap
// Retinem pentru fiecare catun cea mai apropiata fortareata.
// Cand distanta de la un nod fortareata la un nod catun
// este mai mica decat distanta pana la nodul catun, rescriem
// vectorul de distante si cea mai apropiata fortareata.
// Daca gasim un catun la aceeasi distanta minima fata de
// doua fortarete o alegem pe cea mai mica

#include <bits/stdc++.h>
using namespace std;

ifstream in("catun.in");
ofstream out("catun.out");

vector <int> fortareata;
vector <int> distanta;
vector <pair <int, int >> *g;
priority_queue <pair <int, int>, vector <pair <int, int>>, greater<>> heap;

int n, m, k, x, y, z;


int main() {
    in >> n >> m >> k;
    fortareata.resize(n + 1);
    distanta.assign(n + 1, INT_MAX);
    g = new vector <pair <int, int>> [n + 1];

    for(int i = 0; i < k; i++) {
        in >> x;
        fortareata[x] = x;
        heap.push({0, x});
        distanta[x] = 0;
    }

    for(int i = 0; i < m; i++) {
        in >> x >> y >> z;
        g[x].emplace_back(make_pair(y, z));
        g[y].emplace_back(make_pair(x, z));
    }

    // Dijkstra Algorithm
    while(!heap.empty()){
        int nod = heap.top().second;
        int cost = heap.top().first;
        heap.pop();

        for (auto const& vecin: g[nod]) {
            if (cost + vecin.second < distanta[vecin.first]) {
                distanta[vecin.first] = cost + vecin.second;
                heap.push({distanta[vecin.first], vecin.first});
                fortareata[vecin.first] = fortareata[nod];
            }
            else if (cost + vecin.second == distanta[vecin.first]) {
                fortareata[vecin.first] = min(fortareata[vecin.first], fortareata[nod]);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (fortareata[i] == i)
            out << 0 << ' ';
        else
            out << fortareata[i] << ' ';
    }

    return 0;
}