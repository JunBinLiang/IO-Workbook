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

const int N = 2e5 + 10;
vector<int> g[N];
bool vis[N];
int cnt = 0;
void dfs(int u) {
    cnt++;
    vis[u] = true;
    for(int v : g[u]) {
        if(!vis[v]) dfs(v);
    }
}

void solve() {
    int n, l, r;
    cin >> n >> l >> r;
    for(int i = 0; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    memset(vis, 0, sizeof vis);
    int state = 0;
    for(int i = 1; i <= n; i++) {
        if(!vis[i]) {
            cnt = 0;
            dfs(i);
            if(cnt < l + r) {
                state ^= (cnt / (l));
            }
        }
    }

    cout << (state != 0 ? "Alice" : "Bob") << endl;
}     

int main() {
    int t = 1;
    //std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
