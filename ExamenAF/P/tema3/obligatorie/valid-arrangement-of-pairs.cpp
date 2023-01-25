//problema poate fi redusa la gasirea unui ciclu eulerian
// calculam gradul pentru fiecare nod dupa care vom parcurge graful plecand din nodul care are gradul 1
// vom folosi o stiva pentru a parcurge graful (in cazul in care graful este un intreg ciclu atunci putem pleca din orice nod)
// repetam procesul pana cand stiva devine goala

class Solution {
public:
    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        int m = pairs.size();

        unordered_map<int, stack<int>> adj;
        unordered_map<int, int> in;
        unordered_map<int, int> out;

	adj.reserve(m);
	in.reserve(m);
	out.reserve(m);

        for (int i = 0; i < m; i++) {
            int u = pairs[i][0], v = pairs[i][1];
            in[v]++;
            out[u]++;
            adj[u].push(v);
        }

        int start = -1;
        for (auto& p : adj) {
            int i = p.first;
            if (out[i] - in[i] == 1) start = i;
        }
        if (start == -1) {
			start = adj.begin()->first;
        }
        vector<vector<int>> ans;
        euler(adj, ans, start);
        reverse(ans.begin(), ans.end());
        return ans;
    }
private:
    void euler(unordered_map<int, stack<int>>& adj, vector<vector<int>>& ans, int curr) {
        auto& stk = adj[curr];
        while (!stk.empty()) {
            int nei = stk.top();
            stk.pop();
            euler(adj, ans, nei);
            ans.push_back({curr, nei});
        }
    }
};
