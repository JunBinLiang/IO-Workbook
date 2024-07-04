#include<iostream>

using namespace std;

void solve() {
    int a, b, c, d, n;
    cin >> a >> b >> c >> d >> n;
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        if(i % a == 0 || i % b == 0 || i % c == 0 || i % d == 0) {
            ans++;
        }
    }
    cout << ans << endl;
}

int main() {
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
