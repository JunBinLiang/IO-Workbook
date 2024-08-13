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

void solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }

    sort(a.begin(), a.end());
    long long rsum = 0, lsum = 0;
    for(int i = 0; i < a.size(); i++) rsum += a[i].first;
    vector<long long> ans(n);
    for(int i = 0; i < a.size(); i++) {
        long long s = rsum - (a[i].first + 0ll) * (n - i);
        s += (n - i);
        s += ((a[i].first + 0ll) * i - lsum);
        s += i;
        ans[a[i].second] = s;
        rsum -= a[i].first;
        lsum += a[i].first;
    }

    for(long long i : ans) cout << i << " ";
    cout << endl;
    
}    

int main() {
    int t = 1;
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
