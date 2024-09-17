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
    int L, R;
    cin >> L >> R;

    int l = 1, r = R;
    int ans = 0;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        long long add = (1ll + mid) * mid / 2;
        if(L + add <= R) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    } 
    cout << ans + 1 << endl;

}     

int main() {
    int t = 1;
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
