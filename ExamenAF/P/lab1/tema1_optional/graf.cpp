#include <bits/stdc++.h>
using namespace std;

int n, m, x, y;
vector<int> graf[10000];
queue<int> q;

ifstream fin("graf.in");
ofstream fout("graf.out");

int dist2[10000], dist1[10000];
int f[10000];

void bfs(int nod, int dist[]){

    dist[nod] = 1;
    q.push(nod);

    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int i = 0; i < graf[u].size(); i++)
            if(!dist[graf[u][i]]) {
                dist[graf[u][i]] = dist[u] + 1;
                q.push(graf[u][i]);
            }
    }
}

int main()
{
    fin>>n>>m>>x>>y;
    for(int i = 1; i <= m; i++) {
        int a, b;
        fin>>a>>b;
        graf[a].push_back(b);
        graf[b].push_back(a);
    }

    bfs(x, dist1);
    bfs(y, dist2);

    for(int i = 1; i <= n; i++)
        if(dist1[i] + dist2[i] - 1 == dist1[y])
            f[dist1[i]]++;
        else dist1[i] = 0;

    int nrn = 0;
    for(int i = 1; i <= n; i++)
        if(f[dist1[i]] == 1)
            nrn++;

    fout<<nrn<<endl;

    for(int i = 1; i <= n; i++)
        if( f[dist1[i]] == 1)
            fout<<i<<' ';

    return 0;
}
