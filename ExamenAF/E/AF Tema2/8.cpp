// Algoritmul lui Kruskal
// Parcurgem q queries si unim muchiile cu cost mai mic decat cel din query
// Vectorul ans va fi construit ulterior cu true daca exista drum intre nodurile din query si cu false altfel

#include <bits/stdc++.h>
using namespace std;

ifstream in("graf.in");

vector<int> tata;

int Find(int nod) {
    if(tata[nod]==nod)
        return nod;
    return tata[nod]=Find(tata[nod]);
}

void Union(int x, int y){
    int radx = Find(x);
    int rady = Find(y);
    tata[radx] = rady;
}


vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {

    tata.resize(n + 1);

    for (int i = 1; i <= n; ++i)
        tata[i] = i;

    for (int i = 0; i < (int) queries.size(); i++)
        queries[i].push_back(i);

    sort(edgeList.begin(), edgeList.end(), [](auto &a, auto &b) { return a[2] < b[2]; });
    sort(queries.begin(), queries.end(), [](auto &a, auto &b) { return a[2] < b[2]; });

    int i = 0;
    vector<bool> ans((int) queries.size(), false);

    for (auto it: queries) {
        while (i < edgeList.size() && edgeList[i][2] < it[2]) {
            Union(edgeList[i][0], edgeList[i][1]);
            i++;
        }

        ans[it[3]] = (Find(it[0]) == Find(it[1]));
    }

    return ans;
}

int main(){
    vector<vector<int>> muchii = {{0,1,10},{1,2,5},{2,3,9},{3,4,13}}, q = {{0,4,14},{1,4,13}};

    int N=4;

    vector<bool> ans = distanceLimitedPathsExist(N, muchii, q);

    for (auto x: ans)
        cout << x << " ";
    return 0;
}
