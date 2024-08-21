#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<unordered_set>
#include<map>
#include<string>
#include <string.h>
#include <bitset>
#include <queue>

using namespace std;

void solve() {
    int n;
    cin >> n;
    string s = to_string(n);
    if(s.size() < 3) {
        cout << "NO" << endl;
        return;
    }

    if(s[0] != '1' || s[1] != '0') {
        cout << "NO" << endl;
        return;
    }

    if(s[2] == '0') {
        cout << "NO" << endl;
        return;
    }

    int x = s[2] - '0';
    if(s.size() == 4) {
        x = x * 10 + s[3] - '0';
    }
    if(x < 2) {
        cout << "NO" << endl;
        return;
    }
    cout << "YES" << endl;

}    

int main() {
    int t = 1;
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
