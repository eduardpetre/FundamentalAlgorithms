//Dijkstra longest path
//calculam costul maxim de la start la end
//folosind Dijkstra pornim de la start si extindem costul maxim pana la end urmand drumurile cu cel mai mare cost

#include <bits/stdc++.h>
using namespace std;

ifstream in("maxProb.in");

double maxProbability(int n, vector <vector<int>> edges, vector<double> succProb, int start, int end) {
    vector<double> maxProb;
    maxProb.resize(n);

    vector < vector < pair < int, double>>> g;
    g.resize(n);
    priority_queue <pair<double, int>> heap;

    heap.push({1.0, start});
    maxProb[start] = 1.0;

    for (int i = 0; i < edges.size(); i++) {
        g[edges[i][0]].emplace_back(edges[i][1], succProb[i]);
        g[edges[i][1]].emplace_back(edges[i][0], succProb[i]);
    }

    // Dijkstra Algorithm
    while (!heap.empty()) {
        int nod = heap.top().second;
        double cost = heap.top().first;
        heap.pop();

        for (auto const &vecin: g[nod]) {
            if (maxProb[vecin.first] < vecin.second * cost) {
                maxProb[vecin.first] = vecin.second * cost;
                heap.push({maxProb[vecin.first], vecin.first});
            }
        }
    }
    return maxProb[end];
}

int main() {
    int n, m;
    in >> n >> m;

    vector <vector<int>> graph;
    vector<int> edge;
    vector<double> prob;
    int x, y;
    double p;
    for (int i = 0; i < m; i++) {
        in >> x >> y;

        edge.clear();
        edge.push_back(x);
        edge.push_back(y);

        graph.push_back(edge);

        in >> p;
        prob.push_back(p);
    }

    int s, e;
    in >> s >> e;

    cout << n << endl;
    for (int i = 0; i < m; i++)
        cout << prob[i] << " ";
    cout << endl;
    cout << s << " " << e << endl << endl;
    cout << maxProbability(n, graph, prob, s, e);

    return 0;
}

