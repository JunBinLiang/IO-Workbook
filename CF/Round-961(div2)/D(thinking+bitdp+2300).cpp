#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<unordered_set>
#include<string>
#include <string.h>

using namespace std;
using ll = long long;

int bitcount(int n, int c) {
    int ans = 0;
    for(int i = 0; i < c; i++) {
        if(n & (1 << i)) ans++;
    }
    return ans;
}

void solve() {
    int n, c, k;
    string s;
    cin >> n >> c >> k >> s;
    vector<vector<int>> p(c, vector<int>(n));
    for(int i = 0; i < n; i++) {
        p[s[i] - 'A'][i] = 1;
        for(int j = 0; j < c; j++) {
            if(i > 0) p[j][i] += p[j][i - 1];
        }
    }

    vector<bool> dp(1 << c);
    for(int i = 0; i < n; i++) {
        int r = min(i + k - 1, n - 1);
        int st = 0;
        for(int j = 0; j < c; j++) {
            int cnt = p[j][r];
            if(i) cnt -= p[j][i - 1];
            if(cnt == 0) {
                st |= (1 << j);
            }
        }
        dp[st] = true;
    }
    
    for(int st = (1 << c); st >= 0; st--) {
        for(int i = 0; i < c; i++) {
            if(st & (1 << i)) {
                dp[st ^ (1 << i)] = dp[st ^ (1 << i)] | dp[st];
            }
        }
    }

    int ans = c;
    for(int i = 0; i < (1 << c); i++) {
        if(!dp[i]) {
            ans = min(ans, bitcount(i, c));
        }
    }
    cout << ans << endl;

}    

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
