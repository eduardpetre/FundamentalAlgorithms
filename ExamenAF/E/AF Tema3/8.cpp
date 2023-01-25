#include <bits/stdc++.h>

using namespace std;

ifstream in("fmcm.in");
ofstream out("fmcm.out");

vector<vector<int>> graph, capacity, cost, flow;
int n, start, final, maxFlow, totalCost;
vector<int> parent, minDist, newDist, dist;

priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > h;


// Bellman Ford clasic
// Calculam distantele minime de la nodul de start la toate celelalte
void Bellman_Ford() {

    dist.assign(n + 1, INT_MAX);
    queue<int> q;

    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {

        int currentNode = q.front();
        q.pop();

        for (auto neigh: graph[currentNode]) {
            if (flow[currentNode][neigh] < capacity[currentNode][neigh] &&
                dist[neigh] > dist[currentNode] + cost[currentNode][neigh]) {
                dist[neigh] = dist[currentNode] + cost[currentNode][neigh];
                q.push(neigh);
            }
        }
    }
}

// Dijsktra
int Dijkstra() {
    int minFlow = INT_MAX;

    parent.assign(n + 1, 0);
    minDist.assign(n + 1, INT_MAX);

    minDist[start] = 0;
    newDist[start] = 0;
    h.push({0, start});

    while (!h.empty()) {
        int node = h.top().second;
        if (minDist[node] < h.top().first) {
            h.pop();
            continue;
        }
        else h.pop();

        for (auto const &neighbor: graph[node]) {

            int distBetween = cost[node][neighbor] + dist[node] - dist[neighbor];

//            Daca muchia nu este saturata si distanta minima este mai mica decat cea a vecinului atunci se actualizeaza vectorii de distnte
            if (flow[node][neighbor] < capacity[node][neighbor] && minDist[neighbor] > minDist[node] + distBetween) {
                minDist[neighbor] = minDist[node] + distBetween;
                newDist[neighbor] = newDist[node] + cost[node][neighbor];
                parent[neighbor] = node;
                h.push({minDist[neighbor], neighbor});
            }
        }
    }
    if (minDist[final] == INT_MAX)
        return 0;

    //    calculam minFlow-ul
    int i = final;
    while (parent[i] != 0) {
        minFlow = min(minFlow, capacity[parent[i]][i] - flow[parent[i]][i]);
        i = parent[i];
    }

    //    actualizam  flow-ul
    i = final;
    while (parent[i] != 0) {
        flow[parent[i]][i] += minFlow;
        flow[i][parent[i]] -= minFlow;
        i = parent[i];
    }

//    calculam maxFlow-ul si actualizam costul total
    maxFlow += minFlow;
    totalCost += minFlow * newDist[final];

    for (i = 1; i <= n; i++)
        dist[i] = newDist[i];
    return 1;
}

int m, i, x, y, z, c;

int main() {
    in >> n >> m >> start >> final;

    graph.resize(n + 1);
    parent.resize(n + 1);
    newDist.resize(n + 1);
    minDist.resize(n + 1);
    dist.resize(n + 1);

    capacity.resize(n + 1, vector<int>(n + 1));
    cost.resize(n + 1, vector<int>(n + 1));
    flow.resize(n + 1, vector<int>(n + 1));

    for (i = 1; i <= m; i++) {
        in >> x >> y >> c >> z;
        graph[x].push_back(y);
        graph[y].push_back(x);
        capacity[x][y] = c;
        cost[x][y] = z;
        cost[y][x] = -z;
    }

    Bellman_Ford();

//    pana cand nu mai exista drum de la start la final
    while (Dijkstra());

    out << totalCost;
    return 0;
}