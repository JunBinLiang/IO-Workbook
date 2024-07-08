#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;
const int N = 805, INF = 1e5;

int dp[N][N];
vector<int> shift;
int dfs(vector<int>& a, int l, int r) { // k from outside
    if(l + 1 == r) {
        return dp[l][r] = shift[l];
    }

    if(shift[l] == INF) {
        return dp[l][r] = INF;
    }

    if(dp[l][r] != -1) {
        return dp[l][r];
    }

    int ans = INF;
    for(int i = l + 1; i <= r; i += 2) {
        int add = i - l + 1;
        if(i == l + 1) {
            int right = dfs(a, i + 1, r) - add;
            ans = min(ans, max(shift[l], right));
        } else {
            if(i + 1 > r) {
                int left = dfs(a, l + 1, i - 1);
                if(left <= shift[l]) {
                    ans = min(ans, shift[l]);
                }
            } else {
                int left = dfs(a, l + 1, i - 1);
                int right = dfs(a, i + 1, r) - add;
                if(left <= shift[l]) {
                    ans = min(ans, max(shift[l], right));
                }
            }
        }
    }
    return dp[l][r] = ans;
} 

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    shift = vector<int>(n + 1, INF);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        if(i >= a[i] && (i - a[i]) % 2 == 0) {
            shift[i] = i - a[i];
        }
    }
    
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            dp[i][j] = -1;
        }
    }

    for(int l = 1; l <= n; l++) {
        for(int r = l + 1; r <= n; r += 2) {
            dfs(a, l, r);
        }
    }

    vector<vector<bool>> f(n + 1, vector<bool>(n + 1));
    f[0][0] = true;
    for(int r = 1; r <= n; r++) {
        for(int l = r - 1; l >= 1; l -= 2) {
            for(int k = 0; k <= l - 1; k++) {
                if(f[l - 1][k] && dp[l][r] <= k) {
                    f[r][k + (r - l + 1)] = true;
                }
            }
        }

        for(int k = 0; k <= r; k++) {
            f[r][k] = f[r][k] | f[r - 1][k];
        }
    }

    int ans = 0;
    for(int k = 0; k <= n; k++) {
        if(f[n][k]) {
            ans = max(ans, k);
        }
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

/*
1
6
1 3 3 2 4 5 
*/
