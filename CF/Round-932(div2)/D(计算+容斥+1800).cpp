#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)

//2:55 - 3:18
void solve() {
  int n, c;
  scanf("%d%d", &n, &c);
  vector<int> a(n);
  for(int i = 0; i < n; i++) scanf("%d", &a[i]);

  ll ans = (c + 1ll) * (c + 2) / 2;
  ll s = 0;
  for(int i = 0; i < n; i++) {
    int x = a[i];
    if(x % 2 == 0) {
      s += (x / 2 + 1);
    } else {
      s += (x / 2 + 1);
    }
    s += (c - x + 1);
  }

  int o = 0, e = 0;
  for(int i = n - 1; i >= 0; i--) {
    int x = a[i];
    if(x % 2 == 1) o++;
    else e++;
    if(x % 2 == 1) s -= o;
    else s -= e;
  }
  
  printf("%lld\n", ans - s);
}


int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}

