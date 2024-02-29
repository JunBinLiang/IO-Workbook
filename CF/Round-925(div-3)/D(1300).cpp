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

//7:01 - 7:04
void solve() {
  int n, x, y;
  cin >> n >> x >> y;
  vector<int> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }

  ll ans = 0;
  map<pair<int, int>, int> f;
  for(int i = 0; i < n; i++) {
    pair<int, int> p = {a[i] % x, a[i] % y};
    pair<int, int> t = {(x - p.first) % x, p.second};
    if(f.find(t) != f.end()) {
      ans += f[t];
    }
    f[p]++;
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

