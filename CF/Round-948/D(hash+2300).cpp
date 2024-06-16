#include "bits/stdc++.h"
 
using namespace std;
 
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
 
void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<bool>> table(n, vector<bool>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c;
            cin >> c;
            table[i][j] = c - '0';
        }
    }
    vector<long long> rands(n), rands2(n);
    for (int i = 0; i < n; ++i) {
        rands[i] = rnd();
        rands2[i] = rnd();
    }
    map<pair<long long, long long>, int> ans;
    int res = 0;
    pair<int, int> ind_ans = {0, 0};
    for (int j = 0; j < m; ++j) {
        long long summ = 0, summ2 = 0;
        for (int i = 0; i < n; ++i) {
            if (table[i][j]) {
                summ ^= rands[i];
                summ2 ^= rands2[i];
            }
        }
        for (int i = 0; i < n; ++i) {
            summ ^= rands[i];
            summ2 ^= rands2[i];
            ans[{summ, summ2}]++;
            if (res < ans[{summ, summ2}]) {
                res = ans[{summ, summ2}];
                ind_ans = {j, i};
            }
            summ ^= rands[i];
            summ2 ^= rands2[i];
        }
    }
    cout << res << "\n";
    string inds(n, '0');
    for (int i = 0; i < n; ++i) {
        if (table[i][ind_ans.first]) {
            if (i != ind_ans.second) {
                inds[i] = '1';
            }
        } else if (ind_ans.second == i) {
            inds[i] = '1';
        }
    }
    cout << inds << "\n";
}
