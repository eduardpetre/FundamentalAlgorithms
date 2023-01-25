#include <bits/stdc++.h>
using namespace std;

ifstream fin("graf.in");

//vector<vector<int>> graf;
vector<pair<int, pair<int, int>>> graf;
int parinte[1000], rg[10000];
int n = 3;

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



int main(){
    vector<vector<int>> arr = {{3, 12}, {-2, 5}, {-4, 1}};
    //int n = arr.size();
    config_kruskal();
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){

            int weight = abs(arr[i][0] - arr[j][0]) + abs(arr[i][1] - arr[j][1]);//manhattan distance

            graf.push_back({weight, {i, j}});

            }
    }

    // sort on edge weight (first element in pair)
    sort(graf.begin(), graf.end());

    int sum = 0;

    // for each edge we travel
    for(int i = 0; i < graf.size(); i++)   {

        int a = Find(graf[i].second.first); // first node
        int b = Find(graf[i].second.second); // second node

        if(a != b){ // if both parents are not same then add weight
            sum += graf[i].first;
            Union(a, b); // now merge them
        }
    }

    cout<<sum; // finally return sum
}
