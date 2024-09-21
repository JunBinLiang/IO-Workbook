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
const int MOD = 998244353;
const int N = 50000 + 10;
int dp[N][(1 << 10) + 1];
int newsts[10][(1 << 10) + 5];
int f[10];
void solve() {
    int n, m;
    cin >> n >> m;
    memset(f, 0, sizeof f);
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        f[u] |= (1 << v);
        f[v] |= (1 << u);
    }

    memset(newsts, -1, sizeof newsts);
    for(int d = 0; d < 10; d++) {
        for(int st = 0; st < (1 << 10); st++) {
            int newst = st;
            for(int j = 0; j < 10; j++) {
                if((newst & (1 << j))) {
                    if((f[j] & (1 << d)) == 0) {
                        newst ^= (1 << j);
                    } else if(d > j) {
                        newst = -1;
                        break;
                    }
                }
            }
            if(newst != -1) newst |= (1 << d);
            newsts[d][st] = newst;
        }
    }


    memset(dp, 0, sizeof dp);
    for(int i = 0; i < 10; i++) {
        dp[n - 1][1 << i] = 1;
    }

    for(int i = n - 2; i >= 0; i--) {
        for(int d = 0; d < 10; d++) { //add this digit
            for(int st = 0; st < (1 << 10); st++) {
                if(newsts[d][st] == -1) continue;
                int nextst = newsts[d][st];
                dp[i][nextst] += dp[i + 1][st];
                dp[i][nextst] %= MOD;
            }
        }
    }

    long long ans = 0;
    for(int st = 0; st < (1 << 10); st++) {
        ans += dp[0][st];
        ans %= MOD;
    }
    cout << ans << endl;
}     

int main() {
    int t = 1;
    //std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
