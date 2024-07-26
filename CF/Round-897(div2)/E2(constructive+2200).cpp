#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<string>
#include <string.h>

using namespace std;
using ll = long long;


int n, k;

int ask(int i) {
    cout << "? " << i << endl;
    int xo;
    cin >> xo;
    return xo;
}

void solve() {
    cin >> n >> k;
    
    int ans = 0, j = 1;
    for(int i = 1; i + k - 1 <= n; i += k) {
        ans ^= ask(i);
        j = i;
    }

    if(k % n != 0) {
        int m = n % k;
        int last = ask(j);
        ans ^= last;
        int x = ask(j + m / 2);
        int y = ask(j + m);
        ans ^= last ^ (x ^ y);
    }
    cout << "! " << ans << endl;
}    

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
