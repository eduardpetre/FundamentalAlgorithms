#include <bits/stdc++.h>
using namespace std;
ifstream f("graf.in");
vector<vector<int>> graph;
vector<int> viz, niv_min, nivel;
stack<pair<int, int>> st;
int n,m;
vector<pair<int,int>> critical_edges;
vector<vector<pair<int,int>>> componente_biconexe;
vector<int> critical_vertexes;

void dfs(int x){
    viz[x]=1;
    niv_min[x]=nivel[x];
    for(int i=0;i<graph[x].size();i++){
        if(viz[graph[x][i]]==0){
            nivel[graph[x][i]]=nivel[x]+1;
            st.push({x, graph[x][i]});
            dfs(graph[x][i]);

            niv_min[x]=min(niv_min[x], niv_min[graph[x][i]]);
            vector<pair<int,int>> c;
            if(niv_min[graph[x][i]]==nivel[x]){
                critical_vertexes.push_back(x);
                pair<int, int> edge = st.top();
                while(edge.first != x || edge.second != graph[x][i]){
                    c.push_back({edge.first, edge.second});
                    st.pop();
                    edge=st.top();

                }
                c.push_back({edge.first, edge.second});
                st.pop();

            }

            if(niv_min[graph[x][i]]>nivel[x]){
                critical_vertexes.push_back(x);
                critical_edges.push_back({x, graph[x][i]});
                pair<int, int> edge = st.top();
                while(edge.first != x || edge.second != graph[x][i]) {
                    c.push_back({edge.first, edge.second});
                    st.pop();
                    edge=st.top();

                }
                c.push_back({edge.first, edge.second});
                st.pop();


            }
            if(c.size()){
                componente_biconexe.push_back(c);
            }

        }else{
            if(nivel[graph[x][i]]<nivel[x]-1){
                niv_min[x]=min(niv_min[x], nivel[graph[x][i]]);
                st.push({x, graph[x][i]});
            }
        }
    }
}

int main() {

    f>>n>>m;
    graph.resize(n+2);
    for(int i=0;i<m;i++){
        int x,y;
        f>>x>>y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    viz.resize(n+2);
    niv_min.resize(n+2);
    nivel.resize(n+2);

    for(int i=1;i<=n;i++){
        if(viz[i]==0){
            dfs(i);
        }
    }

    cout<<"Muchii critice:\n";
    for(int i=0;i<critical_edges.size();i++){
        cout<<critical_edges[i].first<<" - "<<critical_edges[i].second<<"\n";
    }



    cout<<"\n\n Componentele biconexe sunt:\n";
    for(int i=0;i<componente_biconexe.size();i++){
        for(int j=0;j<componente_biconexe[i].size();j++){
            cout<<componente_biconexe[i][j].first<<" - "<<componente_biconexe[i][j].second<<"     ";
        }
        cout<<"\n";
    }

    cout<<"\n Nodurile critice sunt:\n";
    for(int i=0;i<critical_vertexes.size();i++){
        cout<<critical_vertexes[i]<<" ";
    }
    return 0;
}
