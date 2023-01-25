#include <bits/stdc++.h>
using namespace std;

ifstream fin("lesbulan.in");
ofstream fout("lesbulan.out");

vector<vector<int>>graf;
vector<bool>viz;
int t,n,m;
bool ciclu = false;

void dfs(int nod, int parinte){
    viz[nod] = true;
     for(auto it : graf[nod]){
        if(it != parinte){
            if(viz[it]) {
                ciclu = true;
                return;
            }
            dfs(it, nod);
        }
    }
}

void sterge_frunze(){
    vector<int> frunze;
    for(int i = 1; i<=n; i++)
        if(graf[i].size()==1)
            frunze.push_back(i);

     for(auto node : frunze)
        if(graf[node].size()){
            int next = graf[node][0];
            graf[next].erase(find(graf[next].begin(), graf[next].end(), node));
            graf[node].pop_back();
        }
    frunze.clear();
}

int exec(){
    for(int i=1; i<=n; i++)
        if(!viz[i])
            dfs(i, 0);
    if(ciclu)   return false;
    sterge_frunze();
    sterge_frunze();
    for(int i=1; i<=n; i++)
        if(graf[i].size() > 2)
            return false;
    return true;
}

int main(){
    fin >> t;
    while(t--){
        ciclu=false;
        fin >>n >>m;
        graf.clear();
        viz.clear();
        graf.resize(n+1);
        viz.resize(n+1, false);
        while(m--){
            int x,y;
            fin >>x >>y;
            graf[x].push_back(y);
            graf[y].push_back(x);
        }
        fout<<exec()<<'\n';
    }
    return 0;
}
