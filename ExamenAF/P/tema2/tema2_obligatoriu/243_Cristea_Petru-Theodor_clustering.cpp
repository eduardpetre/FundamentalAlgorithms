#include <bits/stdc++.h>

using namespace std;

struct obj{
    string s1, s2;
    int val;
};

int k, N;
vector <obj> cuv_dist;
unordered_map <string, int> clusterWord;

ifstream fin("graf.in");

int distLev(string s1, string s2) {
    int l1 = s1.length();
    int l2 = s2.length();

    int dp[2][l1 + 1];
    memset(dp, 0, sizeof(dp));

    for (int i = 0; i <= l1; i++)
        dp[0][i] = i;

    for (int i = 1; i <= l2; i++) {
        for (int j = 0; j <= l1; j++) {
            if (j == 0)
                dp[i % 2][j] = i;
            else if (s1[j - 1] == s2[i - 1])
                dp[i % 2][j] = dp[(i - 1) % 2][j - 1];
            else
                dp[i % 2][j] = 1 + min(dp[(i - 1) % 2][j], min(dp[i % 2][j - 1], dp[(i - 1) % 2][j - 1]));
        }
    }

    return dp[l2 % 2][l1];
}


bool cmp(obj a, obj b) {
    return a.val < b.val;
}

int main() {
    int k;
    cout<<"k="; cin>>k;

    int ct = 0;
//citesc cuvintele
    vector<string> cuvinte;
    while(!fin.eof()){
        string cuv;
        fin>>cuv;
        cuvinte.push_back(cuv);
        ct++;
    }

    //calculez distantele levstein
    for (int i = 0; i < ct; ++i) {
        for (int j = i + 1; j < ct; ++j) {
            int levDist = distLev(cuvinte[i], cuvinte[j]);
            cuv_dist.push_back({cuvinte[i], cuvinte[j], levDist});
        }
    }

    sort(cuv_dist.begin(), cuv_dist.end(), cmp);

    //atribui cate un cluster pt fiecare cuvant initial
    for (int i = 1; i <= cuvinte.size(); ++i)
        clusterWord[cuvinte[i - 1]] = i;

    //repartizam cuvintele in k clase cuvintele care au distante cat mai apropiate
    for (int i = 1; i <= ct - k; ++i) {
        int j = 0;
        while (clusterWord[cuv_dist[j].s1] == clusterWord[cuv_dist[j].s2])
            ++j;

        //iau clusterul fiecarui cuvant si unesc clusterul cu val mai mare de cel cu val mai mica
        int cluster1 = clusterWord[cuv_dist[j].s1];
        int cluster2 = clusterWord[cuv_dist[j].s2];
        int minCluster = min(cluster1, cluster2);
        for (auto& cuv: clusterWord)
            if (cuv.second == cluster1 || cuv.second == cluster2)
                cuv.second = minCluster;
    }

    //calculam gradul de separare
    int minDif = 2e9;
    for (auto cluster1: clusterWord) {
        for (auto cluster2: clusterWord) {
            //daca cuvintele nu s in acelasi cluster
            if (cluster1.second != cluster2.second) {
                //aflu distanta minima dintre oricare doua clustere
                int dif = distLev(cluster1.first, cluster2.first);
                if (dif < minDif)
                    minDif = dif;
            }
        }
    }

    //afsez cuvintele din fiecare cluster
    for (int i = 1; i <= ct; ++i) {
        bool hasWord = false;
        for (auto cuv: clusterWord) {
            if (cuv.second == i) {
                cout << cuv.first << " ";
                hasWord = true;
            }

        }
        if (hasWord) {
            cout << '\n';
        }
    }
    cout << minDif;
}
