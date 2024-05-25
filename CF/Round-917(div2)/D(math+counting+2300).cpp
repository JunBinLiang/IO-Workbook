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

const int MOD = 998244353;
const int SIZE = 1e6 + 100;
struct Fenwick {
  ll tree[SIZE];
  void init(int n) {
    for(int i = 0; i <= n + 1; i++) tree[i] = 0;
  }

  void update(int i, int val) {
    i++;
    while(i < SIZE){
      tree[i] += val;
      i += (i & -i);
    }
  }

  ll pre(int i) {
    ll sum = 0;
    while(i>0){
      sum += tree[i];
      i -= ( i & -i);
    }
    return sum;
  }
  ll query(int i, int j) {
      return ((pre(j + 1) - pre(i)) % MOD + MOD) % MOD;
  }
} tr[21];


int pack(int highbit, int x) {
  int v = 1 << highbit;
  while(x < v) x *= 2;
  return x;
}


void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<int> a(n), b(m);
  ll ans = 0;
  for(int i = 0; i < n; i++) scanf("%d", &a[i]);
  for(int i = 0; i < m; i++) scanf("%d", &b[i]);

  tr[0].init(m + 10);
  ll s = 0;
  for(int i = 0; i < m; i++) {
    s += tr[0].query(b[i] + 1, m + 1);
    tr[0].update(b[i], 1);
  }

  for(int i = 0; i < 21; i++) tr[i].init(max(4 * n + 10, m + 10));

  int highbit = -1;
  for(int x : a) {
    for(int i = 0; i < 21; i++) {
      if(x & (1 << i)) highbit = max(highbit, i);
    }
  }

  ans += s * n;
  ans %= MOD;

  for(int i = n - 1; i >= 0; i--) {
    int bit = -1;
    for(int j = 0; j < 21; j++) {
      if(a[i] & (1 << j)) {
        bit = j;
      }
    }

    for(int j = 0; j < 21; j++) {
      int d = abs(bit - j);
      ll ls = tr[j].query(0, pack(highbit, a[i]) - 1);
      ll rs = tr[j].query(pack(highbit, a[i]) + 1, 4 * n + 5);
      if(j < bit) {
        ll cnt1 = (d + 1ll + m) * (max(0, m - d)) / 2;
        if(d + 1 >= m) cnt1 = ((m + 0ll) * m);
        else cnt1 += ((d + 0ll) * m);
        cnt1 %= MOD;
        ll cnt2 = (d + m + 0ll) * (max(0, m - d + 1)) / 2;
        if(d >= m) cnt2 = ((m + 0ll) * m);
        else cnt2 += ((d - 1ll) * m);
        cnt2 %= MOD;
        ans += (cnt1 * ls);
        ans %= MOD;
        ans += (cnt2 * rs);
        ans %= MOD;
      } else if(j == bit) {
        ll cnt1 = (1ll + m) * m / 2;
        cnt1 %= MOD;
        ll cnt2 = (m - 1ll) * m / 2;
        cnt2 %= MOD;
        ans += (cnt1 * ls);
        ans %= MOD;
        ans += (cnt2 * rs);
        ans %= MOD;
      } else {
        ll cnt1 = (1ll + (m - d)) * (max(0, m - d)) / 2;
        cnt1 %= MOD;
        ll cnt2 = (0ll + (m - d - 1)) * (max(0, m - d)) / 2;
        cnt2 %= MOD;
        ans += (cnt1 * ls);
        ans %= MOD;
        ans += (cnt2 * rs);
        ans %= MOD;
      }
    }
    tr[bit].update(pack(highbit, a[i]), 1);
  }

  printf("%lld\n", ans);
}

  

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
