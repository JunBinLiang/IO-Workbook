#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector


void solve() {
  int n;
  cin >> n;
  vector<ll> a(n);
  for(int i = 0; i < n; i++) cin >> a[i];
  sort(a.begin(), a.end());

  int g = -1;
  for(int i = 1; i < n; i++) {
    int d = a[i] - a[i - 1];
    if(g == -1) g = d;
    else g = __gcd(g, d);
  }

  set<ll> s(a.begin(), a.end());
  ll ans = 0;
  ll last = a.back();
  for(int i = 0; i <= n; i++) {
    last -= g;
    if(s.find(last) == s.end()) {
      s.insert(last);
      break;
    }
  } 

  for(auto v : s) {
    ans += ((a.back() - v) / g);
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
