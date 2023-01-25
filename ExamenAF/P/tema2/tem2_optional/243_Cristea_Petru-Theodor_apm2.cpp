#include <bits/stdc++.h>

using namespace std;

ifstream fin("apm2.in");
ofstream fout("apm2.out");

int parinte[10001], n, m, q;

struct muchie
{
	int x, y, cost;
}v[100001], a[100001];
vector<muchie> sol;


int cost_cmp(muchie a, muchie b){
	return a.cost < b.cost;
}

int Find(int x)
{
    if (parinte[x] == x)
        return x;
    parinte[x] = Find(parinte[x]);
    return parinte[x];

}

void Union(int x, int y)
{
	parinte[Find(x)] = Find(y);
}

int main()
{
	fin >> n >> m >> q;
	for (int i = 1; i <= m; ++i)
		fin >> v[i].x >> v[i].y >> v[i].cost;

    //sortam muchiile dupa cost
	sort(v + 1, v + m + 1, cost_cmp);


    //configuram pt kruskal
	for (int i = 1; i <= n; ++i)
		parinte[i] = i;


    int cost_min=0;
	//kruskal propriu zis
	for (int i = 1; i <= m; ++i)
	{

		if (Find(v[i].x) != Find(v[i].y)){
			Union(Find(v[i].x), Find(v[i].y));
            cost_min += v[i].cost;
            sol.push_back(v[i]);
        }
    }


    while(q){
        long long x, y, cost_min2=0;
        fin>>x>>y;
        for (int i = 1; i <= n; ++i)
            parinte[i] = i;

        Union(x,y);

        for(int i=0; i < (int)sol.size(); i++)
            if(Find(sol[i].x) != Find(sol[i].y)){
                Union(sol[i].x, sol[i].y);
                cost_min2 += sol[i].cost;
            }

        fout<<cost_min-cost_min2-1<<"\n";
        q--;
    }
}
