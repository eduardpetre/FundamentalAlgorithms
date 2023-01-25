#include <bits/stdc++.h>
using namespace std;
ifstream f("graf.in");
vector<vector<int>> graph;
int n,m,k;
vector<int> source, father, height;
vector<tuple<int, int, int>> edges;
vector<tuple<int, int, int>> edges_apm;
vector<int>max_app;

bool cmp(tuple<int, int, int> edge_one, tuple<int, int, int> edge_two){
    return get<2>(edge_one) < get<2>(edge_two);
}

void initializare(int x){
    father[x]=x;
    height[x]=0;
}

int reprezentant(int u){
    if(father[u]==u){
        return u;
    }
    father[u]=reprezentant(father[u]);
    return father[u];
}

void reuneste(int u, int v){
    int ru, rv;
    ru= reprezentant(u);
    rv= reprezentant(v);
//    if(source[ru]==1 or source[rv]==1){
//        source[ru]=1;
//        source[rv]=1;
//        source[u]=1;
//        source[v]=1;
//    }



    if(source[rv]==1){
        father[ru]=rv;
        source[ru]=1;
//        source[u]=1;
    }else{
        if(source[ru]==1){
            father[rv]=ru;
            source[rv]=1;
//            source[v]=1;
        }else{
            if(height[ru]>height[rv]){
                father[rv]=ru;
            }else{
                father[ru]=rv;
                if(height[ru]==height[rv]){
                    height[rv]=height[rv]+1;
                }
            }
        }

    }
}


int main() {

    f>>n>>m;
    graph.resize(n+1);
    source.resize(n+1);
    father.resize(n+1);
    height.resize(n+1);
    for(int i=0;i<m;i++){
        int x,y,cost;
        f>>x>>y>>cost;
        graph[x].push_back(y);
        graph[y].push_back(x);
        tuple<int, int, int> edge;
        edge = {x, y, cost};
        edges.push_back(edge);

    }

    sort(edges.begin(), edges.end(), cmp);
    for(int i=1;i<=n;i++){
        initializare(i);
    }

    f>>k;

    for(int i=0;i<k;i++){
        int x;
        f>>x;
        source[x]=1;
    }

    for(int i=0;i<m;i++){
        if(reprezentant(get<0>(edges[i])) == reprezentant(get<1>(edges[i])) or (source[reprezentant(get<0>(edges[i]))]==1 && source[reprezentant(get<1>(edges[i]))]==1)){
            continue;
        }
        reuneste(get<0>(edges[i]), get<1>(edges[i]));
        edges_apm.push_back(edges[i]);
    }
    cout<<"Muchiile din apm sunt:\n";
    for(int i=0;i<edges_apm.size();i++){
        cout<<"Muchia "<<get<0>(edges_apm[i])<<" - "<<get<1>(edges_apm[i])<<" cu costul "<<get<2>(edges_apm[i])<<"\n";
    }

    max_app.resize(n+1);
    for(int i=1;i<=n;i++){
        max_app[reprezentant(i)]++;
    }
    int maxim=0;
    int most_important;
    for(int i=1;i<=n;i++){
        if(max_app[i]>maxim){
            most_important=i;
            maxim=max_app[i];
        }
    }
    cout<<most_important;


    return 0;
}
