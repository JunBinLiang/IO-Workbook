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
#include <random>
#include <chrono>

using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)

const int MOD  = 1e9 + 7;

ull cross(pair<ull, ull> p1, pair<ull, ull> p2) {
  if(p1.first > p2.first) swap(p1, p2);
  if(p2.first > p1.second) return 0;
  return (min(p1.second, p2.second) - p2.first + 1); 
}

ull get(ll n) {
  if(n == 0) {
    return 0;
  }
  ull ans = 0;
  for(int i = 0; i < 62; i++) {
    ull count = (1ll << i);
    ull L = count, R = count * 2 - 1;
    if(n >= count) {
      if(i > 1) {
        ull p = 1;
        for(int j = 0; j <= 60 && p <= R; j++) {
          ull a = p, b = p * i - 1;
          ans += (j * cross({L, R}, {a, b}));
          ans %= MOD;
          p *= i;
        }
      }
      n -= count;
    } else {
      if(i > 1) {
        ull L = count, R = count + n - 1;
        ull p = 1;
        for(int j = 0; j <= 60 && p <= R; j++) {
          ull a = p, b = p * i - 1;
          ans += (j * cross({L, R}, {a, b}));
          ans %= MOD;
          p *= i;
        }
      }
      break;
    }
  }
  return ans;
}

void solve() {
  ll L, R;
  scanf("%lld%lld", &L, &R);
  printf("%lld\n", ((get(R) - get(L - 1)) + MOD) % MOD);
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
