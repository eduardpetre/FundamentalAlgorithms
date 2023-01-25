#include <bits/stdc++.h>

using namespace std;

ifstream fin ("retea2.in");
ofstream fout("retea2.out");

int n,m,i,j;
pair<int, int> v[4010];
long double distanta[4010];
int vizitat[4010];

double calc_dist(int x, int y, int a, int b){
    return sqrt(1LL * (x-a) * (x-a) + 1LL * (y-b) * (y-b));
}

int main()
{
    fin>>n>>m;

    for(int i = 1; i <= n+m; i++)
        fin>>v[i].first>>v[i].second; //vector de perechi care retine coordonatele

    for (i=2;i<=n+m;i++)
        distanta[i] = 1000000;  //initializam distantele

    long double sol = 0;


    for (i=1;i<=n+m;i++){

        long double mini = 1000000; int nod = 0;

        for (j=1;j<=n+m;j++){
            if (!vizitat[j] && distanta[j] < mini){ //retinem distanta minima si nodul (daca acesta nu a mai fost vizitat ca fiecare
                                                                                            //bloc sa fie luat doar odata)
                mini = distanta[j];
                nod = j;
            }}

        vizitat[nod] = 1;

        if (i == 1){
            for (j=1;j<=n+m;j++){
                if (j <= n)  //centrala care produce curent
                    distanta[j] = 0;
                else distanta[j] = calc_dist (v[1].first,v[1].second,v[j].first,v[j].second);  //calculeaza distanta de la
//cate un bloc la prima centrala (sa avem cu ce compara distantele)
            }

        } else {
            sol += mini;  //adaugam cate o distanta la solutie pentru a le conecta pe toate
            for (j=1;j<=n+m;j++){
                long double cost = calc_dist (v[nod].first,v[nod].second,v[j].first,v[j].second); //calculam distantele ramase
                if (!vizitat[j] && cost < distanta[j]) //aflu distanta de la blocul curent la cea mai apropiata sursa de energie
                    distanta[j] = cost;
            }
        }
    }

    fout<<setprecision(7)<<fixed<<sol;

}
