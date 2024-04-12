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
  ll n, p, l, t;
  cin >> n >> p >> l >> t;
  
  ll task = (n - 1) / 7 + 1;
  ll d = task / 2;
  if(task % 2 == 1) d++;

  if(task * t + (d * l) >= p) {
    ll L = 1, R = d;
    ll ans = -1;
    while(L <= R) {
      ll mid = L + (R - L) / 2;
      if(min(task, mid * 2) * t + mid * l >= p) {
        ans = mid;
        R = mid - 1;
      } else {
        L = mid + 1;
      }
    }
    cout << n - ans << endl;
  } else {
    p -= task * t;
    p -= d * l;
    ll ans = d;
    ans += (p / l);
    if(p % l != 0) ans++;
    cout << n - ans << endl;
  }

}


int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
