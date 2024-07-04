#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;
//4:22 - 4:43
void solve() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<vector<int>> a(n + 1);
    for(int i = 1; i <= n; i++) {
        int k;
        scanf("%d", &k);
        a[i] = vector<int>(k, 0);
        for(int j = 0; j < k; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    dp[0][0] = 0;
    int tot = 0;
    for(int i = 1; i <= n; i++) {
        vector<int>& b = a[i];
        int sum = 0;
        for(int x : b) sum += x;

        int sz = b.size(); tot += sz;
        vector<int> c(sz + 1);
        for(int j = 1; j <= sz; j++) {
            int k = sz - j;
            for(int x = 0, s = 0; x < sz; x++) {
                s += b[x];
                if(x + 1 >= k) {
                    c[j] = max(c[j], sum - s);
                    s -= b[x - k + 1];
                }
            }
        }
        c[sz] = sum;

        for(int j = 0; j <= min(tot, m); j++) {
            dp[i][j] = dp[i - 1][j];
            for(int k = 1; k <= min(sz, j); k++) {
                if(j >= k && dp[i - 1][j - k] != -1) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - k] + c[k]);
                    //if(i == 1 && j == 1) {
                      //cout <<"gg " << k << "   " << dp[i - 1][j - k] << "  " << c[k] << endl;
                    //}
                }
            }
            //cout << i << " " << j << "  " << dp[i][j] << endl;
        }
        //cout << endl;
    }
    printf("%d\n", dp[n][m]);
}

int main() {
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
