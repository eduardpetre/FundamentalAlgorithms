#include <bits/stdc++.h>
using namespace std;

//BFS + BitMask
int shortestPathLength(vector<vector<int>> &graph) {

    int n = graph.size(), result = 0;

    queue<vector<int>> q;
    set<pair<int, int>> s;

    //BitMask inlocuieste vectorul visited
    for (int i = 0; i < n; i++) {
        vector<int> v(3, 0);
        int node = i;
        int bitmask = (1 << i);
        int cost = 0;
        v[0] = node;
        v[1] = bitmask;
        v[2] = cost;

        q.push(v);
        s.insert({node, bitmask});
    }

    while (q.size() > 0) {
        auto x = q.front();
        q.pop();

        //daca toate nodurile au fost vizitate (toti bitii 1)
        if (x[1] == (1 << n) - 1) {
            result = x[2];
            break;
        }

        for (auto y : graph[x[0]]) {
            int bitmask = x[1] | (1 << y);
            //verificam daca un bit nu e vizitat
            if (s.find({y, bitmask}) == s.end()) {
                vector<int> v(3, 0);
                v[0] = y;
                v[1] = bitmask;
                v[2] = x[2] + 1;

                q.push(v);
                s.insert({y, bitmask});
            }
        }
    }

    return result;
}

int main() {
    vector<vector<int>> graph {{1,2,3},{0},{0},{0}};
    int res = shortestPathLength(graph);
    cout<<res;
    return 0;
}