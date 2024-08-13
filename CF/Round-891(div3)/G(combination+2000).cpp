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

const int MOD = 998244353;
const int N = 2e5 + 10;
int p[N], sz[N];
int find(int u) {
    return p[u] == u ? u : p[u] = find(p[u]);
}

long long fpow(long long x, long long y){
	long long res = 1;
	while(y){
		if(y & 1) res = (res * x) % MOD;
		x = (x * x) % MOD;
		y >>= 1;
	}
	return res;
}  

void solve() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> e;
    for(int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        e.push_back({w, u, v});
    }

    for(int i = 0; i <= n; i++) {
        p[i] = i;
        sz[i] = 1;
    }

    sort(e.begin(), e.end());
    long long ans = 1;
    for(int i = 0; i < e.size(); i++) {
        int w = e[i][0], u = e[i][1], v = e[i][2];
        int r1 = find(u), r2 = find(v);
        int lsz = sz[r1], rsz = sz[r2];
        long long edges = (lsz + 0ll) * (rsz) - 1;
        ans = ans * (fpow(k - w + 1, edges));
        ans %= MOD;
        sz[r2] += sz[r1];
        p[r1] = r2;
    }
    cout << ans << endl;
}    

int main() {
    int t = 1;
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
