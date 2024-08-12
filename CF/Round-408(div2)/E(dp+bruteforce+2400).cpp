#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<unordered_set>
#include<string>
#include <string.h>
#include <bitset>
#include <queue>

using namespace std;
const int N = 1010;
int p1[N], p2[N];
void solve() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 0; i < N; i++) p1[i] = p2[i] = 0;

    int m1, m2;
    scanf("%d", &m1);
    for(int i = 0; i < m1; i++) {
        int x;
        scanf("%d", &x);
        p1[x] = 1;
    }
    scanf("%d", &m2);
    for(int i = 0; i < m2; i++) {
        int x;
        scanf("%d", &x);
        p2[x] = 1;
    }

    if(m >= ((n / k) + 1) * 2) {
        int ans = 0;
        for(int i = 0; i <= n; i++) {
            if(p1[i] || p2[i]) {
                ans++;
            }
        }
        cout << ans << endl;
        return;
    }

    vector<vector<vector<vector<int>>>> dp(n + 1, vector<vector<vector<int>>>(
        m + 1, vector<vector<int>>(k + 1, vector<int>(k + 1, -10000))
    ));

    dp[0][0][0][0] = 0;
    for(int i = 1; i <= n; i++) {
        dp[i][0][0][0] = 0;
        for(int j = 1; j <= m; j++) {
            for(int a = k; a >= 0; a--) {
                for(int b = k; b >= 0; b--) {
                    int score = min(1, p1[i] + p2[i]);
                    int nexta = (a - 1 + k) % k;
                    int nextb = (b - 1 + k) % k;
                    if(a > 0 && b > 0) {
                        dp[i][j][a - 1][b - 1] = max(dp[i][j][a - 1][b - 1], dp[i - 1][j][a][b] + score);
                    }
                    if(a == 0 && b == 0) {
                        dp[i][j][a][b] = max(dp[i][j][a][b], dp[i - 1][j][a][b]);
                        //use a
                        dp[i][j][nexta][b] = max(dp[i][j][nexta][b], dp[i - 1][j - 1][a][b] + p1[i]);
                        //use b
                        dp[i][j][a][nextb] = max(dp[i][j][a][nextb], dp[i - 1][j - 1][a][b] + p2[i]);
                    } else if(a == 0) {
                        //use a
                        dp[i][j][nexta][b - 1] = max(dp[i][j][nexta][b - 1], dp[i - 1][j - 1][a][b] + p1[i]);
                        //use b
                        dp[i][j][a][nextb] = max(dp[i][j][a][nextb], dp[i - 1][j][a][b] + p2[i]);
                    } else if(b == 0) {
                        //use a
                        dp[i][j][nexta][b] = max(dp[i][j][nexta][b], dp[i - 1][j][a][b] + p1[i]);
                        //use b
                        dp[i][j][a - 1][nextb] = max(dp[i][j][a - 1][nextb], dp[i - 1][j - 1][a][b] + p2[i]);
                    }
                }
            }
        }
    }

    int ans = 0;
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= m; j++) {
            for(int a = 0; a <= k; a++) {
                for(int b = 0; b <= k; b++) {
                    ans = max(ans, dp[i][j][a][b]);
                }
            }
        }
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
