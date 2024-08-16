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
const int N = 2e5 + 10;
long long fact[N];


  


//7:29
void solve() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    int ans = 0;

    vector<int> A = {a, b}, B = {c, d};
    for(int i = 0; i < A.size(); i++) {
        int x1 = A[i], y1 = A[i ^ 1];
        for(int j = 0; j < B.size(); j++) {
            int x2 = B[j], y2 = B[j ^ 1];
            int awin = 0, bwin = 0;
            if(x1 > x2) awin++;
            else if(x1 < x2) bwin++;
            if(y1 > y2) awin++;
            else if(y1 < y2) bwin++;
            if(awin > bwin) ans++;
        }
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
