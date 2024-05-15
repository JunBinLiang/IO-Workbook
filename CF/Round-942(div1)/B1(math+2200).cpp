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

/*void kill() {
  vector<int> a;
  for(int i = 0; i < 1000000; i++) a.push_back(i);
}*/

void solve() {
  int n, m;
  cin >> n >> m;
  
  //g * (x + y) * t = g * b
  // (x + y) * t = b
  // gcd(x, y) = 1 and b = g * y
  // x * t + y * t = g * y
  // x * t = y * (g - t)
  // since gcd(x, y) = 1  =》 gcd(x + y, y) = 1    
  // g % (x + y) == 0

  ll ans = 0;
  //g can not be 1
  for(int x = 1; x * x <= n; x++) {
    for(int y = 1; y * y <= m; y++) {
      if(__gcd(x, y) == 1) {
        ans += min(n / x,m / y) / (x + y);
      }
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
