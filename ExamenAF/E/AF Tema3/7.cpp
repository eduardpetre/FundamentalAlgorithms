#include <iostream>
#include <algorithm>

using namespace std;

string shortestCommonSupersequence(string str1, string str2) {
    int m = str1.size(), n = str2.size();
    int dp[m + 1][n + 1];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    int i = m, j = n;
    string result;
    while (i > 0 && j > 0) {
        if (str1[i - 1] == str2[j - 1]) {
            result.push_back(str1[i - 1]);
            --i;
            --j;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            result.push_back(str1[i - 1]);
            --i;
        } else {
            result.push_back(str2[j - 1]);
            --j;
        }
    }
    while (i > 0) {
        result.push_back(str1[i - 1]);
        --i;
    }
    while (j > 0) {
        result.push_back(str2[j - 1]);
        --j;
    }

    reverse(result.begin(), result.end());
    return result;
}

int main() {
    string str1 = "abac";
    string str2 = "cab";
    cout << shortestCommonSupersequence(str1, str2) << endl;
    return 0;
}