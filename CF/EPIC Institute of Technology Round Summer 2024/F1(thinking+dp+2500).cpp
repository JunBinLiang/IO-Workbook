#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;
const int N = 105;

int dp[N][N][N];
vector<int> shift;
int dfs(vector<int>& a, int l, int r, int k) { // k from outside
    if(l + 1 == r) {
        return dp[l][r][k] = 1;
    }

    if(dp[l][r][k] != -1) {
        return dp[l][r][k];
    }

    int ans = 0;
    int x = shift[l];
    for(int i = l + 1; i <= r; i += 2) {
        int t = 0;
        int add = i - l + 1;
        if(i == l + 1) {
            if(shift[i + 1] != -1 && shift[i + 1] <= 2 + k) {
                t = dfs(a, i + 1, r, shift[i + 1]);
            }
        } else {
            if(shift[l + 1] != -1 && shift[l + 1] <= shift[l]) {
                if(i + 1 > r) {
                    t = dfs(a, l + 1, i - 1, k);
                } else {
                    if(shift[i + 1] != -1 && shift[i + 1] <= k + add) {
                       t = dfs(a, l + 1, i - 1, k) & dfs(a, i + 1, r, shift[i + 1]); 
                    }
                }
            }
        } 
        if(t) {
            ans = 1;
        }
    }
    return dp[l][r][k] = ans;    
} 

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    shift = vector<int>(n + 1, -1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        if(i >= a[i] && (i - a[i]) % 2 == 0) {
            shift[i] = i - a[i];
        }
    }
    
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            for(int k = 0; k <= n; k++) {
                dp[i][j][k] = -1;
            }
        }
    }

    for(int l = 1; l <= n; l++) {
        for(int r = l + 1; r <= n; r += 2) {
            if(shift[l] != -1 && shift[l] <= l - 1) {
                dfs(a, l, r, shift[l]);
            }
        }
    }

    vector<vector<bool>> dp1(n + 1, vector<bool>(n + 1, false));
    dp1[0][0] = true;
    int ans = 0;
    for(int r = 1; r <= n; r++) {
        for(int l = r - 1; l >= 1; l -= 2) {
            for(int k = 0; k <= l - 1; k += 2) {
                if(dp1[l - 1][k]) {
                    for(int t = 0; t <= k; t += 2) {
                      if(dp[l][r][t] == 1) {
                        dp1[r][k + (r - l + 1)] = true;
                      }
                    }
                }
            }
        }
        for(int k = 0; k <= r; k++) {
            dp1[r][k] = dp1[r][k] | dp1[r - 1][k];
        }
    }
    
 
    for(int k = 0; k <= n; k++) {
        if(dp1[n][k]) ans = max(ans, k);
    }
    printf("%d\n", ans / 2);    
}   

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
