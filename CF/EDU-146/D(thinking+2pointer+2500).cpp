#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <unordered_set>
#include <string.h>

using namespace std;  
using ll = long long;



const int N = 3010;

struct Tuple {
    ll val;
    int index, w;
    bool operator<(const Tuple& other){
        return val < other.val;
    }
};

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  vector<pair<int, int>> a(n);
  int ans = n;
  for(int i = 0; i < n; i++) scanf("%d", &a[i].first);
  for(int i = 0; i < n; i++) scanf("%d", &a[i].second);
  sort(a.begin(), a.end());

  for(int i = 0; i < n; i++) {
    ll x = (a[i].first + 0ll) * a[i].second;
    ll l = x - k, r = x + k; //range
    vector<Tuple> b;
    for(int j = 0; j < n; j++) {
      if(i == j) continue;
      ll cnt1 = x / a[j].first;
      ll cnt2 = cnt1 + 1;
      ll v1 = cnt1 * a[j].first, v2 = cnt2 * a[j].first, v3 = (a[j].first + 0ll) * a[j].second;
      if(cnt1 > 0 && v1 >= l && v1 <= r) {
        b.push_back({cnt1 * a[j].first, j, 0});
      }
      if(cnt2 > 0 && v2 >= l && v2 <= r) {
        b.push_back({cnt2 * a[j].first, j, 0});
      }
      if(v3 >= l && v3 <= r) {
        b.push_back({(a[j].first + 0ll) * a[j].second, j, 1});
      }
    }
    sort(b.begin(), b.end());
    int lidx = 0, ridx = 0; 
    vector<int> vis(n + 1);
    int sum = 0, cnt = 0;
    for(ll j = l; j <= r; j++) {
      while(ridx < b.size() && b[ridx].val <= j) {
        int index = b[ridx].index;
        if(vis[index] == 0) {
          cnt++;
        }
        sum += b[ridx].w;
        vis[index]++;
        ridx++;
      }
      if(j < x) continue;
      ll left = j - k;
      while(lidx < b.size() && b[lidx].val < left) {
        int index = b[lidx].index;
        vis[index]--;
        if(vis[index] == 0) {
          cnt--;
        }
        sum -= b[lidx].w;
        lidx++;
      }
      if(cnt == n - 1) {
        ans = min(ans, n - (sum + 1));
      }
    }
  }

  printf("%d\n", ans);
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
