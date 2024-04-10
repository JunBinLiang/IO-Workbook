#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector


void solve() {
  ll n, k, x;
  scanf("%lld%lld%lld", &n, &k, &x);
  ll s1 = (n - k + 1ll + n) * k / 2;
  ll s2 = (1ll + k) * k / 2;
  if(x <= s1 && x >= s2) printf("YES\n");
  else printf("NO\n");
}


int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
