#include<bits/stdc++.h>

using namespace std;

ifstream fin("easygraph.in");
ofstream fout("easygraph.out");

int t, n, m;
vector<long long> v;
vector<vector<int>> graf;
vector<long long> S;
vector<bool> vizitat;

void dfs(int nod){
    vizitat[nod] = true;
    S[nod] = max(S[nod], v[nod]);  //pe s[nod] punem initial valoarea nodului care ni se da la inceput
    for(auto fiu: graf[nod]){
        if(!vizitat[fiu])
            dfs(fiu);
        S[nod] = max(S[nod], v[nod] + S[fiu]);  //actualizam s[nod] in functie de ce am parcurs inainte
    }
}

int main(){
    fin>>t;
    while(t--){
        v.clear();
        graf.clear();
        vizitat.clear();
        S.clear();

        fin>>n>>m;

        v.resize(n+1);
        graf.resize(n+1);
        vizitat.resize(n+1, false);
        S.resize(n+1, -1000000);

        for(int i=1; i<=n; i++){
            fin>>v[i];
        }

        for(int i=0; i<m; i++){
            int x, y;
            fin>>x>>y;
            graf[x].push_back(y);
        }
    /*
    for(int i=1; i<=n; i++){
        cout<<i<<": ";
        for(int j=0; j<graf[i].size(); j++)
            cout<<graf[i][j]<<' ';
        cout<<endl;
    }*/
        long long ans = -1000000;
        for(int i = 1; i <= n; i++){
            if(!vizitat[i])
                dfs(i);
            ans = max(ans, S[i]);
        }
        fout << ans << "\n";
    }
}


