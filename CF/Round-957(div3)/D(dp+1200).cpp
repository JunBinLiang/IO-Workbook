#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include <string.h>

using namespace std;
using ll = long long;

void solve() {
    int n, m, k;
    string s;
    cin >> n >> m >> k >> s;
    s = "L" + s;
    int INF =  1e9;
    vector<int> dp(n + 2, INF);
    dp[0] = 0;

    for(int i = 1; i <= n; i++) {
        if(s[i] == 'C') continue;
        
        int add = 0;
        if(s[i] == 'W') add = 1; 
        
        for(int j = i - 1; j >= max(0, i - m); j--) {
          if(s[j] == 'C') continue;
          if(s[j] == 'L') {
            dp[i] = min(dp[i], dp[j] + add);
          } else if(s[j] == 'W' && j + 1 == i) {
            dp[i] = min(dp[i], dp[j] + add);
          }
        }
    }

    for(int i = 0; i <= n; i++) {
        if(s[i] == 'L' && i + m >= n + 1 && dp[i] <= k) {
            cout << "YES" << endl;
            return;
        }
        if(s[i] == 'W' && i + 1 >= n + 1 && dp[i] <= k) {
            cout << "YES" << endl;
            return;
        }
    }
    cout << "NO" << endl;
}    

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
