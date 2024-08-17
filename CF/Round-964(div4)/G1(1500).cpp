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

const int MOD = 1e9 + 7;

int x = 21;
int test(int a, int b) {
    if(a >= x) a++;
    if(b >= x) b++;
    return a * b;
}

int ask(int a, int b) {
    cout << "? " << a << " " << b << endl;
    int val;
    cin >> val;
    return val;
}

void solve() {
    int l = 2, r = 999;
    int ans = -1;
    int cnt = 0;
    while(l + 2 <= r){
        int a = l + max(1, (r - l) / 3);
        int b = l + max(1, (r - l) / 3) * 2;
        int val = ask(a, b); 
        //cout << l << "  " << a << " " << b << "  " << r << "      " << val << endl;
        cnt++;
        if(val == (a + 1) * (b + 1)) { // x <= a, x <= b
            ans = a;
            r = a;
        } else if(val == (a * b)) { // x > a, x > b
            l = b + 1;
        } else if(val == a * (b + 1)) { // x <= b, x > a
            ans = b;
            l = a + 1;
            r = b;
        }
    }

    if(l <= r) {
        if(l == r) ans = l;
        else if(l + 1 == r) {
            int val = ask(l, l);
            if(val == (l + 1) * (l + 1)) ans = l;
            else ans = r;
            cnt++;
        } else {
            int val = ask(l, l + 1);
            if(val == (l + 1) * ((l + 1) + 1)) ans = l;
            else if(val == (l * (l + 1))) ans = l + 1;
            else ans = r;
            cnt++;
        }
    }
    cout << "! " << ans << endl;
}    

int main() {
    int t = 1;
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
