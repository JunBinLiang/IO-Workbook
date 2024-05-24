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
  vector<int> a(n + 1);
  for(int i = 1; i <= n; i++) {
    cin >> a[i];
  }

  ll ans = 0;
  vector<int> b;
  for(int i = 1; i <= n; i++) {
    if(a[i] != i) {
      b.push_back(a[i]);
    }
  }

  sort(b.begin(), b.end());
  if(b.size() == 0) { //already sort
    for(int i = 1; i <= 2 * n; i++) {
      ans += (2 * n - i + 1);
    }
    cout << ans << endl;
    return;
  }

  int mn = b[0], mx = b.back();
  //[L : R]
  // R >= mx + 1
  // L <= mn + n
  for(int i = 1; i <= mn + n; i++) {
    int r = max(mx + 1, i + 1);
    ans += (2 * n - r + 1);
  }
  
  set<int> s;
  bool ok = true;
  for(int i = 1; i <= n; i++) {
    if(a[i] != i) {
      int other = a[a[i]];
      if(other != i) {
        ok = false;
        break;
      }
      s.insert(a[i] + other);
      swap(a[a[i]], a[i]);
    }
  }

  if(ok && s.size() == 1) ans++;
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
