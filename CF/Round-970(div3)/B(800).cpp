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

bool ok(string& s, int n) {
    //n * n
    if(n == 1 || n == 2) {
        return true;
    }
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int p = i * n + j;
            if(i == 0 || i == n - 1 || j == 0 || j == n - 1) {
                if(s[p] == '0') return false; 
            } else {
                if(s[p] == '1') return false; 
            }
        }
    }
    return true;
}

void solve() {
    int n;
    string s;
    cin >> n >> s;
    for(int i = 1; i * i <= n; i++) {
        if(i * i == n) {
            if(ok(s, i)) {
                cout << "YES" << endl;
                return;
            }
            break;
        }
    }
    cout << "NO" << endl;
}     

int main() {
    int t = 1;
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
