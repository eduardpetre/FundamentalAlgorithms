#include <bits/stdc++.h>
using namespace std;

ifstream fin("graf.in");
vector<int> graf[100];
vector<bool> visited;
vector<int> entry, low;
int timer;
int n;

void dfs(int u, int p = -1) {
    visited[u] = true;
    //stocam timpul de intrare si low value
    entry[u] = low[u] = timer++;

    for (int fiu : graf[u]) {
        if (fiu == p)
            continue;

        if (visited[fiu])
            low[u] = min(low[u], entry[fiu]);

        else{
            dfs(fiu, u);
            low[u] = min(low[u], low[fiu]);

            if (low[fiu] > entry[u])
                cout<<u<<' '<<fiu<<endl;
        }
    }
}


int main(){
    fin >> n;
    while(!fin.eof()){
        int nod1, nod2;
        fin>>nod1>>nod2;
        graf[nod1].push_back(nod2);
        graf[nod2].push_back(nod1);
    }

    visited.assign(n, false);
    entry.assign(n, -1);
    low.assign(n, -1);

    for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs(i);
    }
}

