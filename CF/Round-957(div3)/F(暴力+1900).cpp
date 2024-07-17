#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_set>
#include<string>
#include <string.h>

using namespace std;
using ll = long long;

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    int ans = 0;
    for(int i = 0; i < n; i++) {
        int j = i;
        unordered_set<int> s = {x};
        while(j < n) {
            vector<int> temps;
            for(auto val : s) {
                if(val % a[j] == 0) temps.push_back(val / a[j]);
            }
            for(int temp : temps) s.insert(temp);
            if(s.find(1) != s.end()) break;    
            j++;
        }
        ans++;
        i = j - 1;
    }
    cout << ans << endl;
}    

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
