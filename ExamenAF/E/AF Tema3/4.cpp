// Un aranjament valid de perechi este un ciclu eulerian
// Construim graful si numaram gradul de intrare si iesire pentru fiecre nod
// Nodul de start devine nodul cu gradul 1; daca ciclul contine tot graful atunci nodul de start poate fi orice nod
// Parcurgem graful cu ajutorul unei stive si adaugam muchiile in rezultat

#include <bits/stdc++.h>

using namespace std;

void euler(unordered_map<int, stack<int>>& edges, vector<vector<int>>& result, int curr) {
    auto& stk = edges[curr];
    while (!stk.empty()) {
        int neigh = stk.top();
        stk.pop();
        euler(edges, result, neigh);
        result.push_back({curr, neigh});
    }
}

vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
    int m = pairs.size();

    unordered_map<int, stack<int>> edges;
    unordered_map<int, int> degreein;
    unordered_map<int, int> degreeout;

    edges.reserve(m);
    degreein.reserve(m);
    degreeout.reserve(m);

    for (int i = 0; i < m; i++) {
        int x = pairs[i][0], y = pairs[i][1];
        degreein[y]++;
        degreeout[x]++;
        edges[x].push(y);
    }

    int start = -1;
    for (auto& edge: edges) {
        int x = edge.first;
        if (degreeout[x] - degreein[x] == 1)
            start = x;
    }

    if (start == -1) {
        start = edges.begin()->first;
    }

    vector<vector<int>> result;
    euler(edges, result, start);
    reverse(result.begin(), result.end());
    return result;
}

int main() {
    vector<vector<int>> pairs = {{1,  2},
                                 {1,  3},
                                 {2, 1}};
    vector<vector<int>> result = validArrangement(pairs);
    for (auto r: result) {
        cout << "[" << r[0] << ", " << r[1] << "]" << endl;
    }
    return 0;
}
