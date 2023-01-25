#include <bits/stdc++.h>

using namespace std;
ifstream fin("harta.in");
ofstream fout("harta.out");

int n, m, flow, max_flow;;
int graf[300][300], parinte[300];
bool viz [300];

// O(n*m^2)
// folosim algoritmul Edmonds-Karp
// dublam fiecare nod si le memoram de la 1 la n si de la n+1 la 2*n si adaugam un nod sursa numerotat cu 0 si un nod destinatie 2*n+1
// adaugam muchie intre sursa si toate nodurile (prima multime) cu capacitate gradul pentru iesire
// (la fel si pt a doua multime si destinatie pt gradul de intrare)
// adaug muchie de la orice nod din prima multime la orice alt nod din a doua multime cu capacitatea 1

bool bfs () {
    queue<int> q;

    // cu bfs cautam in graful rezidual daca exista un drum din sursa pana in destinatie


    memset(parinte, 0, sizeof(parinte));
    memset(viz, false, sizeof(viz));

    viz[0] = 1;
    q.push(0);
    parinte[0]=-1;

    while (!q.empty()) {

        int nod_curent = q.front();
        q.pop();

        if (nod_curent == 2 * n + 1)
            return true;

        for (int i = 1; i <= 2 * n + 1; i++) {
            if (!viz[i] && graf[nod_curent][i] > 0) {
                viz[i] = 1;
                q.push(i);
                parinte[i] = nod_curent;
            }
        }
    }
    return false;
}

void flow_gen(){
    while(bfs()) {

        int nod;

        for(int i=1; i<=n; i++){
            if (viz[n + i] && graf[n + i][2 * n + 1] > 0) {
                flow = 1000000;
                parinte[2 * n + 1] = n + i;
                for (nod = 2 * n + 1; nod != 0; nod = parinte[nod])
                    flow = min(flow, graf[parinte[nod]][nod]);
                    if (flow == 0)
                        continue;
                    for (nod = 2 * n + 1; nod != 0; nod = parinte[nod]) {
                        graf[parinte[nod]][nod] -= flow;
                        graf[nod][parinte[nod]] += flow;
                    }
                    max_flow += flow;
                }
        }
    }
}


int main (){
    fin>>n;
    for (int i = 1; i <= n; i++) {
        int x, y;
        fin >> x >> y;
        graf[0][i] = x;
        graf[n + i][2 * n + 1] = y;

        for (int j = 1; j <= n; j++)
            if (i != j)
                graf[i][n + j] = 1;
    }

    flow_gen();

    fout<<max_flow<<endl;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            if (graf[i][n + j] == 0 && i != j)
                fout << i << " " << j << endl; //acestea vor fi muchiile saturate
    }

}
