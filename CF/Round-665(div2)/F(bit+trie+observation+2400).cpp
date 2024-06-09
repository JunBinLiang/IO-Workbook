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

const int N = (1 << 19) + 5;
int a[N], tr[N * 19][2];
ll sums[N * 19], tot = 0;
int id = 1;

int change = 0;

void init() {
  id = 1;
  memset(tr, -1, sizeof tr);
  memset(sums, 0, sizeof sums);
}

void update(int n, int newv, int oldv) {
  int u = 0;
  for(int i = 19; i >= 0; i--) {
    int b = 0;
    if(n & (1 << i)) b = 1;
    if(tr[u][b] == -1) {
      tr[u][b] = id++;
    }
    u = tr[u][b];
    sums[u] += newv;
    sums[u] -= oldv;
    //cout << "update " << u << " " << sums[u] << endl;
  }  
  //cout << endl;
}

ll get(int n) { //get the sum of the first n values
  //change ^ i <= n
  ll ans = 0;
  int u = 0;
  for(int i = 19; i >= 0 && u != -1; i--) {
    int b1 = 0;
    if(n & (1 << i)) b1 = 1;
    int b2 = 0;
    if(change & (1 << i)) b2 = 1;
    if(b1 == 0) {
      if(b2 == 0) {
        u = tr[u][0];
      } else {
        u = tr[u][1];
      }
    } else {
      if(b2 == 0) {
        if(tr[u][0] != -1) ans += sums[tr[u][0]];
        u = tr[u][1];
      } else {
        if(tr[u][1] != -1) ans += sums[tr[u][1]];
        u = tr[u][0];
      }
    }
  }
  if(u != -1) ans += sums[u];
  return ans;
}

void solve() {
  init();
  int n, m;
  scanf("%d%d", &n, &m);
  for(int i = 0; i < (1 << n); i++) {
    scanf("%d", &a[i]);
    tot += a[i];
    update(i, a[i], 0);
  }

  for(int i = 0; i < m; i++) {
    int op;
    scanf("%d", &op);
    if(op == 1) { 
      int x, w;
      scanf("%d%d", &x, &w);
      x--;
      int pos = x ^ change;
      int oldv = a[pos];
      a[pos] = w;
      tot -= oldv;
      tot += w;
      update(pos, w, oldv);
    } else if(op == 2) { //reverse
      int k; scanf("%d", &k);
      change ^= ((1 << k) - 1);
    } else if(op == 3) {
      int k; scanf("%d", &k);
      change ^= ((1 << k));
    } else {
      int l, r;
      scanf("%d%d", &l, &r);
      l--; r--;
      ll s1 = get(r);
      if(l > 0) s1 -= get(l - 1);
      printf("%lld\n", s1);
    }
  }
}

int main(){
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
