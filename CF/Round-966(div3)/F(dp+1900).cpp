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
const int INF = 1e9;

int cost(int w, int h, int k) {
    if(w > h) swap(w, h);
    int dif = h - w;
    if(k <= dif) {
        return k * w;
    }
    int ans = dif * w;
    k -= dif;
    //square
    int n = w;

    int last = n, first = last - k / 2 + 1;
    int sum = (first + last) * (k / 2);
    sum -= (k / 2);
    if(k % 2 == 1) sum += (first - 1);
    ans += sum;
    return ans;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> a(n);
    for(int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;

    vector<int> preDp(k + 1, INF);
    preDp[0] = 0;
    for(int i = 0; i < n; i++) {
        int w = a[i].first, h = a[i].second;
        vector<int> curDp(k + 1, INF);
        curDp[0] = 0;
        for(int curk = 1; curk <= k; curk++) {
            curDp[curk] = preDp[curk];
            for(int prek = 0; prek <= curk; prek++) {
                int need = curk - prek;
                if(need <= w + h) {
                  curDp[curk] = min(curDp[curk], preDp[prek] + cost(w, h, need));
                  //cout << w << "  " << h << "     |" << need << "  " << cost(w, h, need) << endl;
                }
            }
        }
        preDp = curDp;
    }
    if(preDp[k] == INF) cout << -1 << endl;
    else cout << preDp[k] << endl;
}    

int main() {
    int t = 1;
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
