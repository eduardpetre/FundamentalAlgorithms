//calculam distanta minima directa de la centrale la blocuri
//folosind Algoritmul lui Prim cautam daca exista distante mai scurte prin intermediul altor blocuri

#include <bits/stdc++.h>
using namespace std;

ifstream in("retea2.in");
ofstream out("retea2.out");

vector<pair<int, int>> blocuri, centrale;
vector<double> distCentrala;
double distantaTotala;
vector<bool> gasit;

double dist(pair<int, int> p1, pair<int, int> p2) {
    return sqrt((pow(p1.first - p2.first, 2)) + pow((p1.second - p2.second), 2));
}

int main() {
    int n, m;
    in >> n >> m;

    int x, y;
    for (int i = 0; i < n; i++) {
        in >> x >> y;
        centrale.emplace_back(x, y);
    }
    for (int i = 0; i < m; i++) {
        in >> x >> y;
        blocuri.emplace_back(x, y);
    }

    distCentrala.resize(m + 1, INT_MAX);

    //calculam distanta minima directa de la centrale la blocuri
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            distCentrala[i] = min(distCentrala[i], dist(blocuri[i], centrale[j]));

    for(int i=0;i<m;i++)
        cout<<distCentrala[i]<<" ";

    gasit.resize(m + 1, false);

    //Algoritmul lui Prim
    for (int i = 0; i < m; i++) {
        double d = INT_MAX;
        int ultim = -1;
        for (int j = 0; j < m; j++) {
            if (!gasit[j]) {
                if (distCentrala[j] < d) {
                    d = distCentrala[j];
                    ultim = j;
                }
            }
        }
        distantaTotala += d;
        for (int j = 0; j < m; j++)
            distCentrala[j] = min(distCentrala[j], dist(blocuri[j], blocuri[ultim]));
        gasit[ultim] = true;
    }
    out << fixed << setprecision(6) << distantaTotala;
    return 0;
}