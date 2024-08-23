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
    int n, m;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    cin >> m;
    while(m--) {
        string s;
        cin >> s;
        if(s.size() != n) {
            cout << "NO" << endl;
            continue;
        }

        map<char, int> match;
        set<int> used;
        bool ok = true;
        for(int i = 0; i < n && ok; i++) {
            if(match.find(s[i]) == match.end()) {
                if(used.find(a[i]) != used.end()) ok = false;
                match[s[i]] = a[i];
                used.insert(a[i]);
            } else {
                if(match[s[i]] != a[i]) {
                    ok = false;
                }
            }
        }
        if(ok) cout << "YES" << endl;
        else cout << "NO" << endl; 
    }
}    

int main() {
    int t = 1;
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
