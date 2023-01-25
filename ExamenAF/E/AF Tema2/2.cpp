//Algoritmul lui Kruskal
//daca se cere reuniune (operatia 1) se trece in vectorul de tati aceeasi radacina pentru ambele valori
//altfel se verifica daca cele doua valori au aceeasi radacina

#include <bits/stdc++.h>
using namespace std;

ifstream in  ("disjoint.in");
ofstream out ("disjoint.out");

vector<int> t;

int rad(int a){
    if (t[a] == a)
        return a;

    return rad(t[a]);
}

int main(){
    int n, m;
    in >> n >> m;

    t.resize(n+1);
    for (int i = 1; i <= n; i++)
        t[i] = i;

    //Kruskal
    int op, x, y;
    for (int i = 0; i < m; i++){
        in >> op >> x >> y;
        if (op == 1) {
            t[rad(y)] = rad(x);
        }
        else {
            if (rad(x) == rad(y)) {
                out << "DA" << '\n';
            }
            else {
                out << "NU" << '\n';
            }
        }
    }
    return 0;
}