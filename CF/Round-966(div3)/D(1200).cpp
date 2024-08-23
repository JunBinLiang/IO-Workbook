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
    string s;
    cin >> n;
    vector<int> a(n);
    long long sum = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    cin >> s;

    long long ans = 0;
    int l = 0, r = s.size() - 1;
    while(l < r) {
        if(s[l] == 'R') {
            sum -= a[l];
            l++;
            continue;
        }
        if(s[r] == 'L') {
            sum -= a[r];
            r--;
            continue;
        }

        ans += sum;
        sum -= a[l];
        sum -= a[r];
        l++;
        r--;
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
