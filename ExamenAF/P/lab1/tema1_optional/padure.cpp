#include <bits/stdc++.h>
using namespace std;

ifstream fin("graf.in");
//ofstream fout("padure.out");

int N, M, pc, pl, cc, cl, maze[1001][1001], c[1001][1001];
int ns[4] = {0, 1, 0, -1}, ev[4] = {-1, 0, 1, 0};

deque< pair < int, int > > drum;


//adaugam la inceputul cozii elementele la care trecem fara sa consumam diamante, iar la finalul cozii elemente care necestia consum de diamante
void LEE(){
    while(!drum.empty()) {
        int x = drum.front().first;
        int y = drum.front().second;

        drum.pop_front();

        for(int i = 0; i < 4; i++) {
            int a = x + ev[i];
            int b = y + ns[i];

            if(maze[x][y] == maze[a][b] && c[x][y] < c[a][b]) {
                c[a][b] = c[x][y]; //acelasi tip de copac, nu consumam diamante
                drum.emplace_front(a, b); //cost avantajos, le dispunem prioritar

            } else if(maze[x][y] != maze[a][b] && c[x][y] + 1 < c[a][b]) {
                c[a][b] = c[x][y] + 1; //trecem la alt tip de copac, consumam un diamant si incrementam costul
                drum.emplace_back(a, b); //punem la final deoarece deplasarea costa un diamant

            }
        }
    }
}

int main() {
    fin>>N>>M>>pl>>pc>>cl>>cc;

    for(int i=1; i<=N; i++)
        for(int j=1; j<=M; j++){
            fin>>maze[i][j];
            c[i][j] = 100000;
        }

    drum.emplace_front(pl, pc);

    c[pl][pc] = 0;

    LEE();

    cout << c[cl][cc];

}
