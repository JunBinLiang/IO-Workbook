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

const int N = 3e5 + 10;
void solve() {
    int n;
    cin >> n;
    vector<pair<long long, int>> stk;
    for(int i = 0; i < n; i++) {
        long long a; int b;
        cin >> a >> b;
        long long premax = 0;
        while(stk.size() > 0) {
            if(stk.back().second == b) {
                a = a + stk.back().first - premax;
                premax = 0;
                stk.pop_back();
            } else {
                if(stk.back().first <= a) {
                    premax = max(premax, stk.back().first);
                    stk.pop_back();
                } else {
                    break;
                }
            }
        }
        
        stk.push_back({a, b});
        cout << stk[0].first << " ";
    }
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
