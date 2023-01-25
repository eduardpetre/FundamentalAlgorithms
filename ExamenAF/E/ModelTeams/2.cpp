#include <bits/stdc++.h>

using namespace std;

ifstream in("sub2.in");
ofstream out("sub2.out");

vector<int> distanta;
vector<pair<int, int >> *g;
vector<vector<pair<int, int>>> muchii;
priority_queue<pair<int, int>> heap;

int n, m, k, x, y, z;


int main() {
    in >> n >> m;

    g = new vector<pair<int, int>>[n + 1];
    muchii.resize(n + 1);
    distanta.assign(n + 1, INT_MAX);


    for (int i = 0; i < m; i++) {
        in >> x >> y >> z;
        g[x].emplace_back(make_pair(y, z));
        g[y].emplace_back(make_pair(x, z));
    }

    in >> k;
    for (int i = 0; i < k; i++) {
        in >> x;
        heap.push({0, x});
        distanta[x] = 0;
    }

    // Dijkstra Algorithm
    while (!heap.empty()) {
        int nod = heap.top().second;
        int cost = heap.top().first;
        heap.pop();

        for (auto vecin: g[nod]) {
            if (cost + vecin.second < distanta[vecin.first]) {
                distanta[vecin.first] = cost + vecin.second;
                heap.push({distanta[vecin.first], vecin.first});
                muchii[vecin.first].push_back(make_pair(nod, vecin.first));
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << distanta[i] << ' ';
    }
    cout<<endl;

    for (int i = 1; i <= n; i++)
        if (muchii[i].size())
            cout << muchii[i][muchii[i].size() - 1].first << " " << muchii[i][muchii[i].size() - 1].second << endl;

    return 0;
}