#include <bits/stdc++.h>

using namespace std;
ifstream fin("input.in");
ofstream fout("input.out");
int n, m, flow[1024][1024];
int max_flow = 0;
vector<int> graf[1024], dgraf[1024]; int capacitate[1024][1024];
bool viz[1024];
int parinte[1024];


// construiesc un graf orientat pentru a putea afla taietura minima si pornesc la fel cu un BFS din nodul 1
// verific daca mai pot trimite flux pe muchie intre doua noduri
// daca nu pot, adaug muchia intr un vector
// daca nu am putut ajunge la final in nodul N afisez taietura minia

void taietura(int node){
    for(int i = 1; i <= n; i++)
        viz[i] = false;
    bool trece = false;
    vector <pair <int, int> > muchii_taiate;
    queue <int> Q;
    Q.push(node);
    viz[node] = true;
    while(!Q.empty()){
        node = Q.front();
        if(node == n)
            trece = true;
        Q.pop();
        for(auto v : dgraf[node]){
            if(capacitate[node][v] - flow[node][v] == 0){
                muchii_taiate.push_back(make_pair(node, v));
                continue;
            }
            if(!viz[v]) {
                viz[v] = true;
                Q.push(v);
            }
        }
    }
    if(!trece){
        cout<<"Taietura minima:\n";
        for(auto m : muchii_taiate)
            cout<<m.first<<' '<<m.second<<endl;
        cout<<"Cost: "<< max_flow;
    }
}

bool bfs (int node) {

    for(int i = 1; i <= n; i++){
        viz[i] = false;
        parinte[i] = 0;
    }
    queue<int> q;

    viz[node] = 1;
    q.push(node);

    while (!q.empty()) {
        //pastram nodurile care inca au capacitate
        node = q.front();
        q.pop();
        for (auto i:graf[node]) {
            if (!viz[i] && capacitate[node][i] - flow[node][i]>0) {
                viz[i] = 1;
                q.push(i);
                parinte[i] = node;
            }
        }
    }

    if(!parinte[n])
        return false;

    for (auto i : graf[node]) {
        if(capacitate[i][node] - flow[i][node] > 0){
            int MinFlow = capacitate[i][node] - flow[i][node];
            for(int j = i; j != 1; j = parinte[j])
                MinFlow = min(MinFlow, capacitate[parinte[j]][j] - flow[parinte[j]][j]);
            flow[i][node] += MinFlow;
            flow[node][i] -= MinFlow;
            for(int j = i; j != 1; j = parinte[j]){
                flow[parinte[j]][j] += MinFlow;
                flow[j][parinte[j]] -= MinFlow;
            }
            max_flow += MinFlow;
        }
    }
    taietura(1);

    return true;
}


int main (){
    fin>>n>> m;
    for (int i=0; i<m; i++) {
        int x,y,z;
        fin>> x >> y >> z;
        dgraf[x].push_back(y);
        graf[x].push_back(y);
        graf[y].push_back(x);
        capacitate[x][y] = z;
    }

    bool repeat = true;
    while(repeat){
        repeat = bfs(1);
    }

}
