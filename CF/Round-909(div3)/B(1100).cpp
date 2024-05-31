#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector



void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }

  ll ans = 0;
  for(int i = 2; i <= n; i++) {
    if(n % i != 0) continue;
    int k = n / i;
    ll s = 0;
    ll mn = 1e18, mx = -1;
    for(int j = 0; j < n; j++) {
      s += a[j];
      if((j + 1) % k == 0) {
        mn = min(mn, s);
        mx = max(mx, s);
        s = 0;
      }
    }
    ans = max(ans, mx - mn);
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
