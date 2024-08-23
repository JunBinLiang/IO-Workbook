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


void solve() {
    int n;
    cin >> n;
    set<int> s;
    bool ok = true;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if(i == 0) {
            s.insert(x);
            continue;
        }
        if(s.find(x - 1) == s.end() && s.find(x + 1) == s.end()) {
            ok = false;
        }
        s.insert(x);
    }
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
