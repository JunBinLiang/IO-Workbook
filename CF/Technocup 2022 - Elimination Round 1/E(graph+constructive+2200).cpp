#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<unordered_set>
#include<string>
#include <string.h>

using namespace std;
using ll = long long;

int find(std :: vector<int>& p, int u) {
    return p[u] == u ? u : p[u] = find(p, p[u]);
}


bool dfs(std :: vector<vector<int>>& g, std :: vector<int>& path, int pa, int u, int target) {
    if(u == target) {
        return true;
    }
    bool ans = false;
    for(int v : g[u]) {
        if(pa == v) continue;
        bool t = dfs(g, path, u, v, target);
        ans |= t;
        if(t) {
          path.push_back(v);
        }
    }
    return ans;
}

void solve() {
    int n, m, q;
    std :: cin >> n >> m;
    std :: vector<vector<int>> g(n + 1);
    std :: vector<int> p(n + 1);
    for(int i = 0; i <= n; i++) p[i] = i;
    for(int i = 0; i < m; i++) {
        int u, v;
        std :: cin >> u >> v;
        int r1 = find(p, u), r2 = find(p, v);
        if(r1 != r2) {
            p[r1] = r2;
            g[u].push_back(v);
            g[v].push_back(u);
        }
    }

    std :: vector<int> in(n + 1);
    std :: vector<vector<int>> ans;
    std :: cin >> q;
    for(int i = 0; i < q; i++) {
        int u, v; //u -> v
        std :: cin >> u >> v;
        in[u]++;
        in[v]++;
        std :: vector<int> path;
        dfs(g, path, -1, u, v);
        path.push_back(u);
        reverse(path.begin(), path.end());
        ans.push_back(path);
        
    }

    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        if(in[i] % 2 == 1) {
            cnt++;
        }
    }

    if(cnt == 0) {
        std :: cout << "YES" << std :: endl;
        for(auto& v : ans) {
            std :: cout << v.size() << std :: endl;
            for(int x : v) std :: cout << x << " ";
            std :: cout << std :: endl;
        }
    } else {
        std :: cout << "NO" << std :: endl;
        std :: cout << cnt / 2 << std :: endl;
    }
}    

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
