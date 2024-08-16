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
    string s, t;
    cin >> s >> t;
    int j = 0;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '?') {
            if(j < t.size()) s[i] = t[j++];
            else s[i] = 'a';
        } else {
            if(j < t.size() && s[i] == t[j]) j++;
        }
    }
    
    if(j < t.size()) cout << "NO" << endl;
    else {
        cout << "YES" << endl;
        cout << s << endl;
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
