#include <bits/stdc++.h>

using namespace std;

ifstream fin("online.in");
ofstream fout("online.out");

int parinte[10001], rg[10001], n, m, q;

struct muchie{
	int x, y, cost;
};

vector<muchie> graf;

int cost_cmp(muchie a, muchie b){
	return a.cost < b.cost;
}

int Find(int nod)
{
	int prev = nod;
	while (parinte[nod] != nod)
		nod = parinte[nod];
	return parinte[nod];

}

void Union(int x, int y)
{
	if (rg[x] < rg[y])
		parinte[x] = y;
	if (rg[x] > rg[y])
		parinte[y] = x;
	if (rg[x] == rg[y])
	{
		parinte[x] = y;
		++rg[y];
	}
}


void config_kruskal(){
    for (int i = 1; i <= n; ++i){
        parinte[i] = i;
        rg[i] = 1;
    }
}

int kruskal(){
    vector<muchie> apm;
    config_kruskal();

    sort(graf.begin(), graf.end(), cost_cmp);

    int s = 0;
    //kruskal propriu zis
    for (int i = 0; i < (int)graf.size(); ++i)
    {
        if (Find(graf[i].x) != Find(graf[i].y)){
            Union(Find(graf[i].x), Find(graf[i].y));
            s+=graf[i].cost;
            apm.push_back(graf[i]);
        }
    }
    graf = apm;
    return s;
}


int main()
{
	fin >> n >> m;
	for (int i = 1; i <= m; ++i){
		muchie a;
		fin >> a.x >> a.y >> a.cost;
		graf.push_back(a);
	}

	//citim drumurile care urmeaza sa fie adaugate

	fout<<kruskal()<<endl;

	int k;
	fin>>k;
	for(int i=0; i<k; i++){
        muchie new_m;
		fin >> new_m.x >> new_m.y >> new_m.cost;
        graf.push_back(new_m);

        fout<<kruskal()<<endl;

	}
}
