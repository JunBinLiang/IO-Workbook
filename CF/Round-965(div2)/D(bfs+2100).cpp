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
int to[N];
void solve() {
    int n, m;
    cin >> n >> m;
    for(int i = 0; i <= n; i++) {
        g[i].clear();
        to[i] = 0;
    }
    for(int i = 0; i < n; i++) {
        g[i].push_back(i + 1);
        to[i] = i + 1;
    }   

    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        to[u] = max(to[u], v);
    }

    queue<int> q;
    q.push(0);
    vector<int> d(n, -1);
    d[0] = 0;
    while(q.size() > 0) {
        int u = q.front(); q.pop();
        for(int v : g[u]) {
            if(d[v] == -1) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
    
    //for(int i = 0; i < n; i++) cout << d[i] << "  " << to[i] << endl;
    //cout << endl;

    /*
        If Bessie on index i,
        Elsie can jump to any index on [0 : i - 1] and do a big jump to pass Bessie
        to[j] - (d[j] + 1) > i
    
    */

    string ans(n - 1, '1');
    set<pair<int, int>> s;
    for(int i = 0; i < n - 1; i++) {
        if(s.size() > 0) {
            auto p = *s.begin();
            if(-p.first > i) {
                ans[i] = '0';
            }
        } 
        s.insert({-(to[i] - (d[i] + 1)), i});
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
