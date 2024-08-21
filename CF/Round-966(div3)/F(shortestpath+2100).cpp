#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<unordered_set>
#include<map>
#include<string>
#include <string.h>
#include <bitset>
#include <queue>

using namespace std;

const int N = 1e5 + 10;
vector<pair<int, pair<int, int>>> g[N];

bool in(int x, int l, int r) {
    return x >= l && x <= r;
}

void solve() {
    int n, m;
    int k, t1, t2;
    scanf("%d%d", &n, &m);
    scanf("%d%d%d", &k, &t1, &t2);
    for(int i = 0; i <= n; i++) g[i].clear();

    for(int i = 0; i < m; i++) {
        int u, v, l1, l2;
        scanf("%d%d%d%d", &u, &v, &l1, &l2);
        g[u].push_back({v, {l1, l2}});
        g[v].push_back({u, {l1, l2}});
    }

    int l = 0, r = k;
    int ans = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        const int INF = 1e9 + 100;
        vector<int> d(n + 1, INF);
        vector<int> st(n + 1);
        d[1] = mid;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({mid, 1});
        while(pq.size() > 0) {
            auto p = pq.top(); 
            pq.pop();
            int u = p.second;
            if(st[u]) continue;
            st[u] = true;
            for(int i = 0; i < g[u].size(); i++) {
                int v = g[u][i].first;
                int l1 = g[u][i].second.first, l2 = g[u][i].second.second;
                if((d[u] >= t1 && d[u] < t2) || (d[u] <= t1 && d[u] + l1 > t1)) { //can not use short
                    int reach = min(d[u] + l2, t2 + l1);
                    if(reach < d[v]) {
                        d[v] = reach;
                        pq.push({d[v], v});
                    }

                } else {
                    if(d[u] + l1 < d[v]) {
                        d[v] = d[u] + l1;
                        pq.push({d[v], v});
                    }
                }
            }
        }

        if(d[n] <= k) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    printf("%d\n", ans);
}    

int main() {
    int t = 1;
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
