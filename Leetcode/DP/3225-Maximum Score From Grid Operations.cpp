const int N = 105;
const long long INF = 1000000000000000LL;
long long dp[N][N][N], mdp[N][N][N];
long long p[N][N];

long long q(int c, int l, int r) {
    if(l > r) return 0;
    return l == 0 ? p[c][r] : p[c][r] - p[c][l - 1];
}

void init(int n) {
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            for(int k = 0; k <= n; k++) {
                dp[i][j][k] = -INF;
                mdp[i][j][k] = -INF;
            }
        }
    }
}

class Solution {
public:
    long long maximumScore(vector<vector<int>>& grid) {
        int n = grid.size();
        for(int c = 0; c < n; c++) {
            long long s = 0;
            for(int r = 0; r < n; r++) {
                s += grid[r][c];
                p[c][r] = s;
            }
        }
        
        init(n);
        for(int i = 0; i <= n; i++) {
            dp[0][i][0] = 0;
            mdp[0][i][0] = 0;
        }
        
        for(int i = 1; i < n; i++) {
            for(int pre = 0; pre <= n; pre++) { //pre column black
                long long pmax = 0;
                for(int cur = 0; cur <= n; cur++) { //current column black
                    if(cur <= pre) {
                        long long score = q(i, cur, pre - 1);
                        dp[i][cur][pre - cur] = max(dp[i][cur][pre - cur], score + mdp[i - 1][pre][0]);
                    } else {
                        if(dp[i - 1][pre][cur - pre - 1] + grid[cur - 1][i - 1] > pmax + grid[cur - 1][i - 1]) {
                            pmax = dp[i - 1][pre][cur - pre - 1] + grid[cur - 1][i - 1];
                        } else {
                            pmax = pmax + grid[cur - 1][i - 1];
                        }
                        dp[i][cur][0] = max(dp[i][cur][0], pmax);
                        dp[i][cur][0] = max(dp[i][cur][0], mdp[i - 1][pre][cur]);
                    }
                }
            }
            
            for(int cur = 0; cur <= n; cur++) {
                for(int free = n; free >= 0; free--) {
                    if(cur + free <= n) {
                        mdp[i][cur][free] = dp[i][cur][free];
                        if(cur + free + 1 <= n) {
                            mdp[i][cur][free] = max(mdp[i][cur][free], mdp[i][cur][free + 1]);
                        }
                    }
                }
            }
        }
        
        long long ans = 0;
        for(int cur = 0; cur <= n; cur++) {
            for(int free = 0; free <= n; free++) {
                if(cur + free <= n) {
                    ans = max(ans, dp[n - 1][cur][free]);
                }
            }
        }
        return ans;
    }
};
