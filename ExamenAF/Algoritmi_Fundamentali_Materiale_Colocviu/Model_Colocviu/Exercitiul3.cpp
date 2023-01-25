#include <bits/stdc++.h>
using namespace std;
//ifstream f("graf.in");
int n,m,k,s,t;
vector<vector<int> > graph;
vector<vector<int> > capacity;
vector<vector<int> > capacity_new;
vector<int>leftt, rightt, father;

bool bfs(){
    vector <bool> viz(n+2);
    queue<int> q;
    q.push(s);
    viz[s]=true;
    father[s]=-1;
    while(!q.empty()){
        int current_node = q.front();
        q.pop();
        for(auto const& adj: graph[current_node]){
            if(!viz[adj] && capacity[current_node][adj]){
                father[adj]=current_node;
                if(adj==t){
                    return true;
                }
                viz[adj]=true;
                q.push(adj);
            }
        }
    }
    return false;
}

bool bfs_k(){
    vector <bool> viz(n+2);
    queue<int> q;
    q.push(s);
    viz[s]=true;
    father[s]=-1;
    while(!q.empty()){
        int current_node = q.front();
        q.pop();
        for(auto adj: graph[current_node]){
            if(!viz[adj] && capacity_new[current_node][adj]){
                father[adj]=current_node;
                if(adj==t){
                    return true;
                }
                viz[adj]=true;
                q.push(adj);
            }
        }
    }
    return false;
}

int edmondsKarp_k(int k){
    long flux_max=0;
    while(bfs_k()){
        int x, y, path_min=INT_MAX;
        for(x=t;x!=s;x=father[x]){
            y=father[x];
            if(capacity_new[y][x] < path_min){
                path_min=capacity_new[y][x];
            }
        }
        for(x=t;x!=s;x=father[x]){
            y=father[x];
            capacity_new[y][x] -= path_min;
            capacity_new[x][y] += path_min;
        }
        flux_max += path_min;
        if(flux_max==k){
            return flux_max;
        }

    }

    return -1;
}


int edmondsKarp(){
    long flux_max=0;
    while(bfs()){
        int x, y, path_min=INT_MAX;
        for(x=t;x!=s;x=father[x]){
            y=father[x];
            if(capacity[y][x] < path_min){
                path_min=capacity[y][x];
            }
        }
        for(x=t;x!=s;x=father[x]){
            y=father[x];
            capacity[y][x] -= path_min;
            capacity[x][y] += path_min;
        }
        flux_max += path_min;
//        if(flux_max==k){
//            return flux_max;
//        }

    }

    return flux_max;
}

int main() {

    cin>>n>>m>>k;
    s=0;
    t=n+1;
    graph.resize(n+2);
    leftt.resize(n+2);
    father.resize(n+2);
    capacity.resize(n+2, vector<int>(n+2));
    capacity_new.resize(n+2, vector<int>(n+2));
    rightt.resize(n+2);
    for(int i=0;i<m;i++){
        int x,y;
        cin>>x>>y;
        graph[x].push_back(y);
        leftt[x]=1;
        rightt[y]=1;
        capacity[x][y]=1;
        capacity_new[x][y]=1;

    }
    for(int i=1;i<=n;i++){
        if(leftt[i]==1){
            graph[s].push_back(i);
            capacity[s][i]=2;
            capacity_new[s][i]=1;
        }
        if(rightt[i]==1){
            graph[i].push_back(t);
            capacity[i][t]=2;
            capacity_new[i][t]=1;
        }
    }

    if(edmondsKarp_k(k)==-1){
        cout<<"Nu se poate\n";
    }else{
        for(int i=1;i<=n;i++){
            for(auto node: graph[i]){
                if(node!=s && capacity_new[i][node]==0 && node!=t){
                    cout<<i<<" "<<node<<"\n";
                }
            }
        }
    }

    father.resize(n+2,0);
    cout<<edmondsKarp()<<"\n";
    for(int i=1;i<=n;i++){
        for(auto node: graph[i]){
            if(node!=s && capacity[i][node]==0 && node!=t){
                cout<<i<<" "<<node<<"\n";
            }
        }
    }
    return 0;
}
