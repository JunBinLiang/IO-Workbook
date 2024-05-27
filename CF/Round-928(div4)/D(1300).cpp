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
  vector<ll> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }

  ll full = 0;
  for(int i = 0; i < 31; i++) {
    full += (1 << i);
  }

  int ans = n;
  map<ll, int> f;
  for(int i = 0; i < n; i++) {
    if(f[full ^ a[i]] > 0) {
        ans--;
        f[full ^ a[i]]--;
    } else {
        f[a[i]]++;
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
