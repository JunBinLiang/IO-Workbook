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
    vector<int> a(n);
    int AND = -1;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        if(AND == -1) AND = a[i];
        AND &= a[i];
    }

    if(AND != 0) {
        cout << 1 << endl;
        return;
    }

    vector<int> b;
    int ans = 0;
    for(int i = 0; i < n; i++) {
        int j = i + 1;
        int curAnd = a[i];
        while(j < n && curAnd != 0) {
            curAnd &= a[j++];
        }
        b.push_back(curAnd);
        i = j - 1;
    }
    if(b.back() == 0) cout << b.size() << endl;
    else cout << b.size() - 1 << endl;
}    

int main() {
    int t = 1;
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
