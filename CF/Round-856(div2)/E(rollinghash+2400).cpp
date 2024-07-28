#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<unordered_set>
#include<string>
#include <string.h>

using namespace std;
using ll = long long;

const int N = 2e5 + 10;
vector<int> g[N];
int a[N], cnt[N];
long long base, MOD;
long long h[N], dp[N];
unordered_set<long long> s;

void dfs1(int pa, int u) {
    if(pa != -1 && g[u].size() == 1) {
        dp[u] = h[0];
        return;
    }
    dp[u] = h[0];
    for(int v : g[u]) {
        if(v == pa) continue;
        dfs1(u, v);
        dp[u] += (dp[v] * base);
        dp[u] %= MOD;
    }
}

void dfs2(int pa, int u) {
    if(pa != -1) {
        long long h1 = (dp[pa] - ((dp[u] * base) % MOD)) % MOD;
        if(h1 < 0) h1 += MOD;
        dp[u] += h1 * base;
        dp[u] %= MOD;
    }

    if(s.find(dp[u]) != s.end()) {
        cnt[u]++;
    }
    for(int v : g[u]) {
        if(v == pa) continue;
        dfs2(u, v);
    }
}

void solve() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    memset(cnt, 0, sizeof cnt);
    vector<int> bases = {11, 103, 317, 3177, 100007};
    vector<long long> mods = {1000000007, 998244533, 998244533, 1000000007, 998244533};
    for(int j = 0; j < bases.size(); j++) {
        MOD = mods[j];
        base = bases[j];
        h[0] = base;
        for(int i = 1; i <= n; i++) { //distance
            h[i] = h[i - 1] * base;
            h[i] %= MOD;
        }

        long long tot = 0;
        for(int i = 1; i < n; i++) {
            tot += h[a[i]];
            tot %= MOD;
        }
        s.clear();
        for(int i = 0; i <= n; i++) {
            s.insert((tot + h[i]) % MOD);
        }
        dfs1(-1, 1);
        dfs2(-1, 1);
    }
    
    vector<int> ans;
    for(int i = 1; i <= n; i++) {
        if(cnt[i] == 5) {
            ans.push_back(i);
        }
    }
    cout << ans.size() << endl;
    for(int x : ans) cout << x << " ";
    cout << endl;
}    

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
