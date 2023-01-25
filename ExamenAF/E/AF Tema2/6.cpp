// calculam suma maxima a fiecarui lant cu ajutorul DFS ului si le adaugam intr un vector
// in fiecare DFS actualizam vectorul selectand maximul dintre valoarea curenta si
// suma nodului curent + suma nodului vecin
// in final se afiseaza suma maxima din vector

#include <bits/stdc++.h>
using namespace std;

ifstream in("easygraph.in");
ofstream out("easygraph.out");

int t, n, m;
vector<int> v;	// vectorul de valori
vector<vector<int>> g;	// lista de adiacenta
vector<long long> suma;
vector<bool> vizitat;
long long sumafinala;

void dfs(int node) {
	vizitat[node] = true;
	suma[node] = v[node];

	for (auto& i : g[node]) {
		if (!vizitat[i]) {
			dfs(i);
		}
		suma[node] = max(suma[i] + v[node], suma[node]);
	}

	sumafinala = max(suma[node], sumafinala);
}

int main() {
	in >> t;

	for (int j = 0; j < t; j++) {
		in >> n >> m;
		v.clear();
		v.resize(n + 1);
        g.clear();
		g.resize(n + 1);
        sumafinala = INT_MIN;

        vizitat.assign(n+1, false);
        suma.assign(n+1, 0);

		for (int i = 1; i <= n; i++) {
			in >> v[i];
		}

        //citesc lista de adiacenta
		for (int i = 0; i < m; i++) {
			int x, y;
			in >> x >> y;
			g[x].push_back(y);
		}

		for (int i = 1; i <= n; i++) {
			if (!vizitat[i]) {
				dfs(i);
			}
		}

		out << sumafinala << endl;

	}

    return 0;
}