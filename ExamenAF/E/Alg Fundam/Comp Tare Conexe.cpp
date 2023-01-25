#include <bits/stdc++.h>
using namespace std;

ifstream in("ctc.in");
ofstream out("ctc.out");

vector<vector<int>> graf, grafTranspus, ctc;
int n, m, nrctc;
vector<int> visit;
stack<int> stk;


//dfs standard
void dfs(int s) {
    visit[s] = 1;

    for (auto neigh: graf[s]) {
        if (!visit[neigh])
            dfs(neigh);
    }

    stk.push(s);
}


//dfs pentru graf transpus
void dfs2(int s) {
    visit[s] = 2;
    ctc[nrctc].push_back(s);

    for (auto neigh: grafTranspus[s]) {
        if (visit[neigh] == 1)
            dfs2(neigh);
    }
}

void CompTareConexe() {

    //parcurgere in adancime a grafului
    visit.assign(n+1,0);
    for(int i=1;i<=n;i++)
        if(!visit[i])
            dfs(i);


    //parcurgerea in adancime a grafului transpus pentru a obtine componentele conexe
    while(!stk.empty()){
        int node = stk.top();

        if (visit[node] == 1) {
            nrctc++;
            dfs2(node);
        }
        stk.pop();
    }
}

int main() {
    in>>n>>m;

    graf.resize(n+1);
    grafTranspus.resize(n+1);
    ctc.resize(n+1);


    //construire graf si graf transpus
    for(int i = 1; i <= m; i++){
        int node, dest;
        in>>node>>dest;
        graf[node].push_back(dest);
        grafTranspus[dest].push_back(node);
    }

    CompTareConexe();


    //afisare
    out << nrctc << endl;
    for (int i = 1; i <= nrctc; i++){
        for (auto x: ctc[i])
            out << x << " ";
        out << "\n";
    }

    return 0;
}