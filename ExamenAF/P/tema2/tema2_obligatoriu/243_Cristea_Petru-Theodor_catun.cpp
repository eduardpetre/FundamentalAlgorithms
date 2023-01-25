#include <bits/stdc++.h>

using namespace std;

ifstream fin("catun.in");
ofstream fout("catun.out");

int ans[36001];
int minim[36001];
vector<pair<int, int>> graf[36001];   //perechi sa tinem distanta
priority_queue<pair<int, int>> q;
int n, m, k;

void dijkstra() {
    while (!q.empty()) {
        int nod = q.top().second;
        q.pop();

        for (auto& v : graf[nod]) {

            if (minim[nod] + v.second < minim[v.first]) {
                //am gasit un drum mai scurt deci actualizam
                minim[v.first] = minim[nod] + v.second;
                q.push(make_pair(-minim[v.first], v.first )); //punem perechea in coada pentru a o utiliza ulterior
                ans[v.first] = ans[nod];

            }
            else if (minim[nod] + v.second == minim[v.first]) {

                ans[v.first] = min(ans[v.first], ans[nod]);

            }
        }
    }
}

int main() {

    fin >> n >> m >> k;

    for (int i = 1; i <= n; i++)
        minim[i] = INT_MAX;      //initial, pt dijkstra setam cu o val mare

    for (int i = 1; i <= k; i++) {
        int x;
        //citim o fortareata (=>distanta 0 pana la cea mai apropiata fortareata)
        fin >> x;
        ans[x] = x;
        q.push({ 0, x });
        minim[x] = 0;
    }

    for (int i = 1; i <= m; i++) {
        int x, y, z;
        fin >> x >> y >> z;
        graf[x].push_back({y, z});  //distanta de la x la y este z
        graf[y].push_back({x, z});  //distanta de la y la x este z
    }

    dijkstra();

    for (int i = 1; i <= n; i++)
        if (ans[i] == i)
            fout << 0 << " ";
        else
            fout << ans[i] << " ";
    return 0;
}
