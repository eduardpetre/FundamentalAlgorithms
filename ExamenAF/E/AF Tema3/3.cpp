#include <bits/stdc++.h>

using namespace std;

ifstream in("harta.in");
ofstream out("harta.out");

int n, start, final, maxFlow;
vector<vector<int>> graph, capacity;
vector<int> parent;
vector<bool> visited;

bool bfs() {
    visited.assign(final + 1, false);
    queue<int> q;

    q.push(start);
    visited[start] = true;
    parent[start] = -1;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (auto const &neighbor: graph[node]) {
            int currentCapacity = capacity[node][neighbor];

            // nodul se ia in considerare daca nu a fost inca vizitat si daca exista capacitate pentru a ajunge in el
            if (currentCapacity != 0 && !visited[neighbor]) {
                parent[neighbor] = node;
                if (neighbor == final)
                    return true;
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    return false; // daca nu s-a ajuns la nodul destinatie
}


// ALGORITMUL EDMONDS-KARP
void EdK() {
    while (bfs()) {

        int minFlow = INT_MAX;
        int i = final;
        while (i != 0) {
            minFlow = min(capacity[parent[i]][i], minFlow);
            i = parent[i];
        }

        i = final;
        while (i != 0) {
            capacity[parent[i]][i] -= minFlow;
            capacity[i][parent[i]] += minFlow;
            i = parent[i];
        }

        maxFlow += minFlow;

    }
    out << maxFlow << endl;
}

int main() {
    in >> n;

    start = 0;
    final = 2 * n + 1;

    graph.resize(final + 1);
    parent.resize(final + 1);
    capacity.resize(final + 1, vector<int>(final + 1, 0));

    for (int i = 1; i <= n; i++)
        for (int j = 1 + n; j <= 2 * n; j++) {
            if (i != j - n) {
                graph[i].push_back(j);
                graph[j].push_back(i);
                capacity[i][j] = 1;

            }
        }
    for (int i = 1; i <= n; i++) {
        int node1, node2;
        in >> node1 >> node2;

        graph[start].push_back(i);
        graph[i].push_back(start);

        graph[final].push_back(i + n);
        graph[i + n].push_back(final);

        capacity[start][i] = node1;
        capacity[i + n][final] = node2;
    }

    EdK();

    for (int i = 1; i <= n; i++)
        for (int j = 1 + n; j <= 2 * n; j++)
            if (capacity[j][i])
                out << i << " " << j - n << endl;

    return 0;
}