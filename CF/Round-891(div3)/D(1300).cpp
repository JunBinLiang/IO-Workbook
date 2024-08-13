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

void solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i + 1;
    }
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a[i].first -= x;
    }
    sort(a.begin(), a.end());
    vector<int> ans;
    for(int i = n - 1; i >= 0; i--) {
        if(a[i].first == a.back().first) {
            ans.push_back(a[i].second);
        }
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for(int i : ans) cout << i << " ";
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
