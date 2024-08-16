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

const int MOD = 1e9 + 7;
const int N = 2e5 + 10;
long long fact[N];


  
void solve() {
    int n, s, m;
    cin >> n >> s >> m;
    vector<pair<int, int>> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }

    sort(a.begin(), a.end());
    bool ok = false;
    for(int i = 0; i < n; i++) {
        if(i == 0) {
            if(a[i].first >= s) ok = true;
        }
        else {
            if(a[i].first - a[i - 1].second >= s) ok = true;
        }
    }
    if(m - a.back().second >= s) ok = true;
    if(ok) cout << "YES" << endl;
    else cout << "NO" << endl;
}    

int main() {
    int t = 1;
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
