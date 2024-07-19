#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include <string.h>

using namespace std;
using ll = long long;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> ans;

    for(int i = n; i > m; i--) {
        ans.push_back(i);
    }

    for(int i = 1; i < m; i++) {
        ans.push_back(i);
    }

    for(int x : ans) cout << x << " ";
    cout << endl;
}    

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
