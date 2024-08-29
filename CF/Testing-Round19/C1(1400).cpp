#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_set>
#include<set>
#include<unordered_map>
#include<map>
#include<string>
#include <string.h>
#include <bitset>
#include <queue>
#include <cmath>

using namespace std;
const int N = 4e5 + 10;
int base = 26, MOD = 1e9 + 7;
long long h[N], p[N];

long long get(int l, int r) {
    if(l == 0) return h[r];
    return (h[r] - (h[l - 1] * p[r - l + 1] % MOD) + MOD) % MOD;
} 

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    long long ha = 0;
    for(int i = 0; i < n; i++) {
        ha = ha * base + s[i] - 'a' + 1;
        ha %= MOD;
        h[i] = ha;
    }

    p[0] = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = p[i - 1] * base;
        p[i] %= MOD;
    }

    for(int i = 0; i < n - 1; i++) {
        int left = i + 1, right = n - left;
        if(left > right) {
            int common = left - right;
            if(get(0, common - 1) == get(i - common + 1, i) && get(i + 1, n - 1) == get(common, i)) {
                cout << "YES" << endl;
                cout << s.substr(0, i + 1);
                return;
            }
        }
    }

    cout << "NO" << endl;
}    

int main() {
    int t = 1;
    //std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
