#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
#include <string.h>

using namespace std;  
using ll = long long;

//8:48 : 9 : 13

ll cal(vector<int>& a, int k, int b, int x) {
  ll ans = -((k - 1ll) * x);
  for(int i = 0; i < a.size(); i++) {
    if(k >= a[i]) {
      ll ways = (a[i] + 0ll) * (a[i] - 1) / 2;
      ans += ways * b;
    } else {
      int m = a[i] % k;
      int c = a[i] / k;
      int tot = a[i];
      for(int j = 0; j < k; j++) {
        ll ways = 0;
        if(j < m) {
          tot -= (c + 1);
          ways += (c + 1ll) * tot;
        } else {
          tot -= c;
          ways += (c + 0ll) * tot;
        }
        ans += ways * b;
      }
    }
  }
  
  return ans;
}

void solve() {
  int n, b, x;
  scanf("%d%d%d", &n, &b, &x);
  vector<int> a(n);
  int s = 0;
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    s += a[i];
  }

  ll ans = 0;
  int l = 1, r = s;
  while(l <= r){
    int mid1 = l + (r - l )/ 3;
    int mid2 = l +(r - l)/ 3 * 2;
    ll ans1 = cal(a, mid1, b, x);
    ll ans2 = cal(a, mid2, b, x);
    ans = max(ans, ans1);
    ans = max(ans, ans2);
    if(ans1 > ans2){
      r = mid2 - 1;
    }
    else{
      l = mid1 + 1;
    }
  }
  cout << ans << endl;
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
