#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include <string.h>

using namespace std;
using ll = long long;

const long long INF = 1000000000000000ll;
void solve() {
    int n;
    cin >> n;

    int sz = 1;
    if(n >= 10) sz = 2;
    if(n == 100) sz = 3;
    
    string s = "";
    for(int i = 0; i < 10; i++) {
        s += to_string(n);
    }

    vector<int> vals(8);
    int val = 0;
    for(int i = 1; i < vals.size(); i++) {
        val = val * 10 + s[i - 1] - '0';
        vals[i] = val;
    }
    
    //n * a - b
    // 1 <= a <= 10000   1 <= b <= min(10000, n * a)
    vector<pair<int, int>> ans;
    for(int a = 1;  a <= 10000; a++) {
        int val = n * a;
        for(int len = 1; len <= 7; len++) {
            int b = a * (sz) - len;
            if((b >= 1 && b <= val && b <= 10000) && (val - b == vals[len])) {
                ans.push_back({a, b});
            }
        }
    }

    cout << ans.size() << endl;
    for(auto& p : ans) {
        cout << p.first << " " << p.second << endl;
    }
}    

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
