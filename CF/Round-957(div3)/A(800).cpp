#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include <string.h>

using namespace std;
using ll = long long;

void solve() {
    int a, b, c;
    cin >> a >> b >> c;
    int ans = 0;
    for(int i = a; i <= a + 5; i++) {
        for(int j = b; j <= b + 5; j++) {
            for(int k = c; k <= c + 5; k++) {
                if(i - a + j - b + k - c == 5) {
                    ans = max(ans, i * j * k);
                }
            }
        }
    }
    cout << ans << endl;
}    

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
