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

const int MOD = 1e9 + 7;


void solve() {
    int a, b;
    cin >> a >> b;
    if(a % 2 == 1) {
        cout << "NO" << endl;
        return;
    }
    if(b % 2 == 0) {
        cout << "YES" << endl;
        return;
    }
    if(a > 0) {
        cout << "YES" << endl;
        return;
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
