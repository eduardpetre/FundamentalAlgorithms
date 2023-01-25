#include <bits/stdc++.h>

using namespace std;
ifstream fin("cuplaj.in");
ofstream fout("cuplaj.out");

int l, r, m, n, x, y, c, s, d;
vector<bool>viz;
vector<int>parinte;
vector<vector<int>>muchie_indice;

struct muchie{
    int x, y, c, poz;
};

vector<muchie>M;

//incepem cu un bfs din nodul 0 la fel ca la flux clasic

int BFS(){
    parinte.clear();
    parinte.resize(n);
    fill(viz.begin(), viz.end(), 0);

    queue<int>q;
    viz[s]=1;
    q.push(s);

    while(!q.empty()){

        int nod_curent = q.front();
        q.pop();

        for(auto aux: muchie_indice[nod_curent]){
            muchie muchie_curenta = M[aux];

            if(!viz[muchie_curenta.y] && muchie_curenta.c>0){
                //actualizam informatiile pt muchie_curenta.y (nodul in care intram)
                q.push(muchie_curenta.y);
                viz[muchie_curenta.y] = 1;
                parinte[muchie_curenta.y] = aux;

                if(muchie_curenta.y == d){
                    return 1;
                }
            }
        }
    }
    return 0;
}


int main(){
    fin>>l>>r>>m;
    n = l+r+2;
    s = 0;
    d = n-1;

    viz.resize(n);
    parinte.resize(n);
    muchie_indice.resize(n);

    int dim = 0;
    for(int i=1; i<=m; i++){
        fin>>x>>y;
        dim += 2;
        M.push_back({x, y+l, 1, dim-1});
        M.push_back({y+l, x, 0, dim-2});
        muchie_indice[x].push_back(dim-2);
        muchie_indice[y+l].push_back(dim-1);
    }

    //sursa -> nod stanga
    for(int i=1; i<=l; i++){
        dim+=2;
        M.push_back({s,i,1,dim-1});
        M.push_back({i,s,0,dim-2});
        muchie_indice[s].push_back(dim-2);
        muchie_indice[i].push_back(dim-1);
    }

    //final -> nod dreapta
    for(int i = 1+l; i<=r+l; i++){
        dim+=2;
        M.push_back({i,d,1,dim-1});
        M.push_back({d,i,0,dim-2});
        muchie_indice[i].push_back(dim-2);
        muchie_indice[d].push_back(dim-1);
    }

    c=0;
    while(BFS()){
        // la fel ca la algoritmul clasic verific daca pot trimite
        // flux muchie si retin si fluxul maxim
        // iar muchiile care vor avea capacitatea ramasa 0 vor fi cele returnate
        for(auto aux:muchie_indice[d]){

            if(viz[M[aux].y] && M[M[aux].poz].c!=0){

                int minim = 1000000;
                muchie mc = M[aux];
                parinte[d] = mc.poz;
                int nod = d;

                while(nod != s){
                    minim = min(minim, M[parinte[nod]].c);
                    nod = M[parinte[nod]].x;
                }
                c += minim;
                nod = d;
                while(nod != s){
                    M[parinte[nod]].c -= minim;
                    M[M[parinte[nod]].poz].c +=minim;
                    nod = M[parinte[nod]].x;
                }
            }
        }
    }

    fout<<c<<"\n";

    for(auto aux: M){
        //alegem muchiile care n au extremitati in capete si au capacitatea ramasa 0
        if(aux.c==0 && aux.x!=s && aux.y!=d && aux.x<aux.y){
            fout<<aux.x << " " << aux.y-l<<"\n";
        }
    }

    return 0;
}
