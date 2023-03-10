#include <bits/stdc++.h>

using namespace std;
ifstream fin("input.in");
ofstream fout("input.out");
int n, m, sursa;

vector<vector <int>> graf;
vector<bool> viz;
vector<int> parinte;
queue<int> q;
vector<vector<int>> capacitate;

// aplicam algoritmul general pentru flux pornind cu un bfs clasic din nodul 1
// sa ajung la nodul N pe muchiile carora nu le-am consumat capacitatea
// pt fiecare drum adun fluxul acestuia intr o variabila de raspuns final

int bfs (int node) {
    fill(viz.begin(), viz.end(), 0);
    viz[node] = 1;
    q.push(node);

    while (!q.empty()) {
        //pastram nodurile care inca au capacitate
        int nod_curent = q.front();
        q.pop();
        for (auto i:graf[nod_curent]) {
            if (!viz[i] && i!=n && capacitate[nod_curent][i]>0) {
                viz[i] = 1;
                q.push(i);
                parinte[i] = nod_curent;
            }
        }
    }

    int max_flow = 0;
    for (auto i : graf[n]) {
        if (!viz[i])
            continue;
        //aflam fluxul minim de pe fiecare nod care a putut fi vizitat in bfs
        int flow_min = capacitate[i][n];
        int v = i;
        while (v != 1) {
            flow_min = min(flow_min, capacitate[parinte[v]][v]);
            v = parinte[v];
        }

        capacitate[n][i] += flow_min;
        capacitate[i][n] -= flow_min;

        v = i;
        //actualizam capacitatile ramase dupa ce extragem fluxul minim
        while (v != 1) {
            capacitate[v][parinte[v]] += flow_min;
            capacitate[parinte[v]][v] -= flow_min;
            v = parinte[v];
        }
        //adaugam la fluxul total al drumului
        max_flow += flow_min;
    }

    return max_flow;
}


int main ()
{
    fin>>n>> m;
    graf.resize(n+1);
    viz.resize(n+1,0);
    capacitate.resize(n+1, vector<int>(n+1, 0));
    parinte.resize(n+1, -1);
    sursa = 1;
    for (int i=0; i<m; i++) {
        int x,y,z;
        fin>> x >> y >> z;
        graf[x].push_back(y);
        graf[y].push_back(x);
        capacitate[x][y] += z;
    }


    int flow_total = 0;

    int flow_drum = bfs(sursa);

    while (flow_drum) {
        flow_total += flow_drum;
        flow_drum = bfs(sursa);
    }

    cout<<flow_total;
}
