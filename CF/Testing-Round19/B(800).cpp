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

void solve() {
    int a, b;
    cin >> a >> b;
    if(1 != a && 1 != b) {
        cout << 1 << endl;
        return;
    }
    if(2 != a && 2 != b) {
        cout << 2 << endl;
        return;
    }
    cout << 3 << endl;
}    

int main() {
    int t = 1;
    //std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
