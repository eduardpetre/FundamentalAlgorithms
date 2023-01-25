#include <bits/stdc++.h>

using namespace std;
ifstream fin("fmcm.in");
ofstream fout("fmcm.out");

vector <int> v[360];
int n,nod_start,nod_final,maxflow,cost_total,min_dist[360],tata[360],new_dist[360],dist[360],C[360][360],cost[360][360],flux[360][360];
queue <int> q;
priority_queue < pair <int,int> , vector <pair <int,int > > , greater < pair <int,int > > > h;


//bellman ford clasic
void Bellman_Ford(){
    int i,nod;

    for(i=1;i<=n;i++)
        dist[i]=INT_MAX/2;

    dist[nod_start]=0;
    q.push(nod_start);

    while(!q.empty()){

        nod=q.front();
        q.pop();

        for(i=0; i<v[nod].size(); i++){
            int vecin=v[nod][i];

            if(flux[nod][vecin] < C[nod][vecin] && dist[vecin]>dist[nod]+cost[nod][vecin]){
                dist[vecin]=dist[nod]+cost[nod][vecin];
                q.push(vecin);
            }
        }
    }
}

//dijkstra+calcul flux
int Dijkstra(){
    int i,nod,flux_min=INT_MAX;

    for(i=1;i<=n;i++)
        min_dist[i]=INT_MAX/2,tata[i]=0;

    min_dist[nod_start]=0;new_dist[nod_start]=0;
    h.push({0,nod_start});

    while(!h.empty()){
        int nod=h.top().second;
        if(min_dist[nod] < h.top().first){
            h.pop();
        continue;
        }
        else h.pop();

        for(i=0;i<v[nod].size();i++){

            int vecin=v[nod][i];
            int dist_intre=cost[nod][vecin]+dist[nod]-dist[vecin];

            if(flux[nod][vecin] < C[nod][vecin] && min_dist[vecin] > min_dist[nod]+dist_intre){
                min_dist[vecin]=min_dist[nod]+dist_intre;
                new_dist[vecin]=new_dist[nod]+cost[nod][vecin];
                tata[vecin]=nod;
                h.push({min_dist[vecin],vecin});
            }
        }
    }
    if(min_dist[nod_final]==INT_MAX/2)
        return 0;

    nod=nod_final;

    while(tata[nod]!=0){
        flux_min=min(flux_min,C[tata[nod]][nod]-flux[tata[nod]][nod]);
        nod=tata[nod];
    }

    nod=nod_final;

    while(tata[nod]!=0){
        flux[tata[nod]][nod]+=flux_min;
        flux[nod][tata[nod]]-=flux_min;
        nod=tata[nod];
    }

    maxflow+=flux_min;
    cost_total+=flux_min*new_dist[nod_final];

    for(i=1;i<=n;i++)
        dist[i]=new_dist[i];
    return 1;
}

int m,i,x,y,z,c;

int main()
{
    fin>>n>>m>>nod_start>>nod_final;

    for(i=1;i<=m;i++){
        fin>>x>>y>>c>>z;
        v[x].push_back(y);
        v[y].push_back(x);
        C[x][y]=c;
        cost[x][y]=z;
        cost[y][x]=-z;
    }

    Bellman_Ford();

    while(Dijkstra());

    fout<<cost_total;
}
