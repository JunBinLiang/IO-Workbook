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
    int n;
    cin >> n;
    int mul = 1;
    long long ans = 0;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        x *= mul;
        mul *= -1;
        ans += x;
    }
    cout << ans << endl;
}    

int main() {
    int t = 1;
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
