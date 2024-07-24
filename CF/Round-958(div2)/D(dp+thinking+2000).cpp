#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<string>
#include <string.h>

using namespace std;
using ll = long long;


const int N = 3e5 + 10;
vector<int> g[N];
long long a[N], dp[N][21];

long long dfs(int pa, int u, int t) {
    if(pa != -1 && g[u].size() == 0) {
        return dp[u][t] = a[u] * t;
    }
    if(dp[u][t] != -1) return dp[u][t];
    long long ans = a[u] * t;
    for(int v : g[u]) {
        if(v == pa) continue;
        long long val = 1000000000000000000ll;
        for(int i = 1; i <= 20; i++) {
            if(i != t) {
                val = min(val, dfs(u, v, i));
            }
        }
        ans += val;
    }  
    return dp[u][t] = ans;  
}


void solve() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }

    for(int i = 0; i <= n; i++) {
        g[i].clear();
        for(int j = 0; j < 21; j++) dp[i][j] = -1;
    }

    for(int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    long long ans = 1000000000000000000ll;
    for(int i = 1; i <= 20; i++) ans = min(ans, dfs(-1, 1, i));

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
