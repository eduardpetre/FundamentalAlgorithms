#include <bits/stdc++.h>
using namespace std;

ifstream fin("graf.in");

vector<vector<int>> arie;
int n;

void parcurge(int i, int j, vector<vector<int>> &arie, vector<pair<int, int>>& insula){
    if(i < 0 || j < 0 || i >= arie.size() || j >= arie[0].size() || arie[i][j]==0) //daca iesim din arie sau daca pozitia curenta nu e o parcela return 0
        return ;
    arie[i][j] = 0;  //marcam parcela ca vizitata
    insula.push_back({i, j}); //adaugam parcela la o insula curenta
    //vizitam urmatoarele pozitii din arie cautand parcele adiacente celei curente
    parcurge(i+1, j, arie, insula);
    parcurge(i-1, j, arie, insula);
    parcurge(i, j-1, arie, insula);
    parcurge(i, j+1, arie, insula);

}

int maxAreaOfIsland(vector<vector<int>> &arie){
    vector<vector<pair<int, int>>> insule;
    vector<pair<int, int>> insula_curenta;
    for(int i = 0; i < arie.size(); i++){
        for(int j = 0; j < arie[0].size(); j++){
            if(arie[i][j] == 1){ //gasim o insula
                insula_curenta.clear(); //se goleste insula pe care vrem sa o formam
                parcurge(i, j, arie, insula_curenta); //formam o insula parcurgand parcelele adiacente
                insule.push_back(insula_curenta); //adaugam fiecare insula gasita in vectorul final
            }
        }
    }

    int maxim = -1;
    for(int i = 0; i<insule.size(); i++){
        int a = insule[i].size();
        maxim = max(maxim, insule[i].size());
    }
    return maxim;
}

int main(){
    arie.resize(8);
    for(int i=0; i<8; i++)
        for(int j=0; j<13; j++){
            int parcela;
            fin>>parcela;
            arie[i].push_back(parcela);
    }
    maxAreaOfIsland(arie);
}
