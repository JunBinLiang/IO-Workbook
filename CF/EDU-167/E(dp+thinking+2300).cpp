#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include <string.h>

using namespace std;
using ll = long long;

const int MOD = 998244353;

const int N = 2e5 + 10;
int dp[N][12], p[N][12];
void solve() {
    int n, k;
    cin >> n >> k;

    for(int i = 0; i <= n; i++) {
        for(int j = 0; j < 12; j++) {
            dp[i][j] = 0;
            p[i][j] = 0;
        }
    }

    //Let's not place a block with length 2 first
    dp[0][0] = 1;
    dp[1][1] = 1;
    p[1][1] = 1; //prefix sum
    for(int i = 2; i <= n; i++) {
        if(i != 2)
          dp[i][1] = 1;
        for(int j = 2; j <= k; j++) {
            //place a bloc with length 1
            if(j == k) {
                dp[i][j] += dp[i - 1][j - 1];
                dp[i][j] %= MOD;
                dp[i][j] += dp[i - 1][j];
                dp[i][j] %= MOD;
                if(i >= 3) {
                    dp[i][j] += p[i - 3][j - 1];
                    dp[i][j] %= MOD;
                    dp[i][j] += p[i - 3][j];
                    dp[i][j] %= MOD;
                }
            } else {
                dp[i][j] += dp[i - 1][j - 1];
                dp[i][j] %= MOD;
                if(i >= 3) {
                    dp[i][j] += p[i - 3][j - 1];
                    dp[i][j] %= MOD;
                }
            }
        }
    
        for(int j = 1; j <= k; j++) {
            p[i][j] = dp[i][j];
            p[i][j] += p[i - 1][j];
            p[i][j] %= MOD;
        }
    }

    long long ans = dp[n][k];
    //place the first with 2, place last with 2
    ans += (dp[n - 2][k - 1] * 2);
    ans %= MOD;
    ans += (dp[n - 2][k] * 2);
    ans %= MOD;
    
    //place first and last with 2 at the same time
    if(n >= 4 && k >= 2) {
        ans += dp[n - 4][k - 2];
        ans %= MOD;
        ans += dp[n - 4][k - 1];
        ans %= MOD;
        ans += dp[n - 4][k];
        ans %= MOD;
    }
    
    cout << ans << endl;
}    

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
