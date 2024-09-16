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


void solve() {
    int n;
    cin >> n;
    vector<int> p(n + 1);
    string s;
    for(int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    cin >> s;
    vector<int> ans(n + 1);
    vector<bool> vis(n + 1);
    for(int i = 1; i <= n; i++) {
        if(vis[i]) continue;
        vector<int> path;
        int u = i;
        while(!vis[u]) {
            vis[u] = true;
            path.push_back(u);
            u = p[u];
        }

        int count = 0;
        for(int com : path) {
            if(s[com - 1] == '0') count++;
        }
        for(int com : path) {
            ans[com] = count;
        }
    }

    for(int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << endl;
}     

int main() {
    int t = 1;
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
