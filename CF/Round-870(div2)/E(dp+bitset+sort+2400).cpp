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
using ll = long long;
const int N = 5010;
std :: vector<int> g[N];
std :: bitset<5000> states[N];
void solve() {
    std :: string strMask(5000, '1');
    int m, n;
    scanf("%d%d", &m, &n);
    std :: vector<int> a(n);
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    for(int i = 0; i < n; i++) states[i] = std :: bitset<5000>(strMask);
    std :: vector<std :: pair<int, int>> b(n);
    bitset<5000> cur(strMask);
    for(int j = 0; j < m; j++) {
        for(int i = 0; i < n; i++) {
            scanf("%d", &b[i].first);
            b[i].second = i;
        }
        std :: sort(b.begin(), b.end());
        cur = std :: bitset<5000>(strMask);
        for(int i = 0; i < n; i++) {
            int k = i;
            while(k < n && b[k].first == b[i].first) {
                cur.flip(b[k++].second);
            }
            for(int x = i; x < k; x++) states[b[x].second] &= cur;
            i = k - 1;
        }
    } 

    std :: vector<int> in(n);
    std :: vector<long long> dp(n, -1);
    std :: queue<int> q;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(states[i].test(j)) {
                g[i].push_back(j);
                in[j]++;
                //cout << "g " << i << " " << j << endl;
            }
        }
    }

    for(int i = 0; i < n; i++) {
        if(!in[i]) {
            q.push(i);
            dp[i] = a[i];
        }
    }
    while(q.size() > 0) {
        int u = q.front(); q.pop();
        for(int& v : g[u]) {
            in[v]--;
            dp[v] = std :: max(dp[v], dp[u] + a[v]);
            if(!in[v]) {
                q.push(v);
            }
        }
    }

    long long ans = 0;
    for(int i = 0; i < n; i++) ans = std :: max(ans, dp[i]);
    printf("%lld\n", ans);
}    

int main() {
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
