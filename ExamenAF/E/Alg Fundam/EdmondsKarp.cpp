// Algoritmul lui Edmonds Karp pentru a optimiza programul

// La fiecare pas construim arborele BFS (excluzand destinatia),
// si acum un drum de la sursa la destinatie e reprezentat de
// un drum de la sursa (care este radacina arborelui) la o frunza legata de destinatie printr-o muchie nesaturata.
// Astfel putem la un pas sa marim fluxul pe un numar maximal de astfel de drumuri, fara a mai reface BFS-ul.
// Ne oprim cand nodul de iesire nu mai este accesibil din nodul de intrare pe graful rezidual
// Complexitate (V * E ^ 2)

#include <bits/stdc++.h>

using namespace std;

ifstream in("maxflow.in");
ofstream out("maxflow.out");

int n, m;
vector <vector<int>> graph, capacity;
vector<int> parent, visited;


// BFS pe graf si returneaza daca exista drum de la sursa la destinatie
bool bfs() {
    parent.assign(n + 1, 0);
    visited.assign(n + 1, 0);
    queue<int> q;

    q.push(1);
    visited[1] = 1;

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        if (node == n) { // daca s-a ajuns la nodul destinatie
            return true;
        }

        for (auto const &neighbor: graph[node]) {
            int currentCapacity = capacity[node][neighbor];

            // nodul se ia in considerare daca nu a fost inca vizitat si daca exista capacitate pentru a ajunge in el
            if (currentCapacity > 0 && !visited[neighbor]) {
                parent[neighbor] = node;
                visited[neighbor] = 1;
                q.push(neighbor);
            }
        }
    }

    return false; // daca nu s-a ajuns la nodul destinatie
}

// ALGORITMUL EDMONDS-KARP
int EdK() {

    int maxFlow = 0;

    while (bfs()) {
        //parcurgem vecinii nodului n
        for (auto const &node: graph[n]) {
            //daca muchia nu e saturata si nodul e vizitat calculam fluxul minim rezidual
            if (capacity[node][n] > 0 && visited[node]) {
//                Parcurgem drumul conform BFS pentru a gasi minimul si reactualizam
//                de pe muchii, in functie de cum apar in parcurgere

                int minFlow = capacity[node][n];
                int i = node;
                while (parent[i]) {
                    minFlow = min(minFlow, capacity[parent[i]][i]);
                    i = parent[i];
                }

                i = node;
                capacity[node][n] -= minFlow;
                capacity[n][node] += minFlow;
                while (parent[i]) {
                    capacity[parent[i]][i] -= minFlow;
                    capacity[i][parent[i]] += minFlow;
                    i = parent[i];
                }

                maxFlow += minFlow;

            }
        }
    }
    return maxFlow;
}

int main() {
    in >> n >> m;
    graph.resize(n + 1);
    parent.resize(n + 1);
    capacity.resize(n + 1, vector<int>(n + 1, 0));

    int x, y, z;
    for (int i = 0; i < m; ++i) {
        in >> x >> y >> z;

        graph[x].push_back(y);
        graph[y].push_back(x);

        capacity[x][y] = z;
    }

    int maxFlow = EdK();
    out << maxFlow << endl;

    // b) Taietura minima (Min-Cut)
    cout << "\nTaietura minima:\n";

    // Mai parcurgem o data graful BFS pentru a vedea care sunt nodurile accesibile din sursa
    bfs();

    for (int i = 1; i <= n; i++) {
        for (auto const &neigh: graph[i]) {
            if (visited[i] && !visited[neigh]) {
                // daca nodul i este accesibil din sursa si nodul adiacent lui i nu este accesibil din sursa
                cout << i << " " << neigh << '\n';
            }
        }
    }

    in.close();
    out.close();
    return 0;
}