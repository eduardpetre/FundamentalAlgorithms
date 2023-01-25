#include <bits/stdc++.h>
using namespace std;

ifstream fin("graf.in");

//vector<vector<int>> graf;
vector<pair<int, pair<int, int>>> graf;
vector<int> parinte;
int n = 3;

 bool cmp(vector<int> &a,vector<int> &b)
    {
        return a[2]<b[2];
    }

int Find(int nod){
	if(parinte[nod]==nod)
        return nod;
    return parinte[nod]=Find(parinte[nod]);

}

void Union(int x, int y){
	int lx = Find(x);
    int ly = Find(y);
    parinte[lx] = ly;
}


int main(){
    vector<vector<int>> muchii = {{0,1,2},{1,2,4},{2,0,8},{1,0,16}}, q = {{0,1,2},{0,2,5}};
    //int n = arr.size();

int m = q.size();
    for(int i = 0;i<m;i++)
        q[i].push_back(i);


   parinte.resize(n, 0);
    for (int i = 0; i < n; i++)
        parinte[i] = i;

    sort(muchii.begin(),muchii.end(),cmp);
    sort(q.begin(),q.end(),cmp);

    int i = 0;
    vector<bool> ans(m,0);

    for(auto it:q){
        while(i<muchii.size() and muchii[i][2]<it[2]){
            Union(muchii[i][0],muchii[i][1]);
            i++;
        }
        ans[it[3]] = (Find(it[0])==Find(it[1]));
    }

    for(auto it: ans)
        cout<<it<<' ';
}
