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


const int N = 50000 + 100, MOD = 1e9 + 7;

int a[N];

struct PersistantTrie {
  int roots[N];
  int tr[N * 33][2];
  int sz[N * 33];
  int id;

  void init() {
    memset(tr, -1, sizeof tr);
    memset(sz, 0, sizeof sz);
    roots[0] = 0;
    id = 1;
  }

  void add(int ith, int x) {
    roots[ith] = id++;
    int pu = roots[ith - 1], u = roots[ith];
    for(int i = 30; i >= 0; i--) {
      int b = 0;
      if(x & (1 << i)) b = 1;
      if(pu == -1) {
        tr[u][b] = id++;
        u = tr[u][b];
        sz[u] = 1;
      } else {
        if(tr[pu][b] == -1) {
          tr[u][b] = id++;
          tr[u][b ^ 1] = tr[pu][b ^ 1];
          u = tr[u][b];
          pu = -1;
          sz[u] = 1;
        } else {
          tr[u][b] = id++;
          tr[u][b ^ 1] = tr[pu][b ^ 1];
          u = tr[u][b];
          pu = tr[pu][b];
          sz[u] = 1 + sz[pu];
        }
      }
    }
  }
  
  int greaterAndEqual(int ith, int x, int mid) { //how many element greater than mid
    int ans = 0;
    int u = roots[ith];
    for(int i = 30; i >= 0 && u != -1; i--) {
      int b1 = 0;
      if(x & (1 << i)) b1 = 1;
      int b2 = 0;
      if(mid & (1 << i)) b2 = 1;
      if(b2 == 0) {
        if(tr[u][b1 ^ 1] != -1) {
          ans += sz[tr[u][b1 ^ 1]];
        }
        u = tr[u][b1];
      } else {
        u = tr[u][b1 ^ 1];
      }
    }
    if(u != -1) ans += sz[u];
    return ans;
  }

  int getSize(int i) {
    int u = roots[i];
    int size = 0;
    if(tr[u][0] != -1) size += sz[tr[u][0]];
    if(tr[u][1] != -1) size += sz[tr[u][1]];
    return size;
  }
} pt;

//general trie
int tr[N * 31][2];
int sz[N * 31];
int c[N * 31][31];
int id = 1;
void add(int n) {
  int u = 0;
  for(int i = 30; i >= 0; i--) {
    int b = 0;
    if(n & (1 << i)) b = 1;
    if(tr[u][b] == -1) {
      tr[u][b] = id++;
    }
    u = tr[u][b];
    sz[u]++;
    for(int j = 30; j >= 0; j--) {
      if(n & (1 << j)) {
        c[u][j]++;
      }
    }
  }
}

ll query1(int x, int k) {
  int u = 0;
  ll ans = 0;
  for(int i = 30; i >= 0 && u != -1; i--) {
    int b1 = 0;
    if(x & (1 << i)) b1 = 1;
    int b2 = 0;
    if(k & (1 << i)) b2 = 1;
    if(b2 == 1) {
      u = tr[u][b1 ^ 1];
    } else {
      if(tr[u][b1 ^ 1] != -1) {
        for(int j = 30; j >= 0; j--) {
          int b = 0;
          if(x & (1 << j)) b = 1;
          if(b == 0) {
            ans += ((c[tr[u][b1 ^ 1]][j] + 0ll) * (1 << j));
          } else {
            ans += ((sz[tr[u][b1 ^ 1]] - c[tr[u][b1 ^ 1]][j] + 0ll) * (1 << j));
          }
          ans %= MOD;
        }
      }
      u = tr[u][b1];
    }
  }
  
  if(u != -1) {
    ans += ((k + 0ll) * sz[u]);
    ans %= MOD;
  }

  return ans;
}

int query2(int x, int k) {
  int u = 0;
  int ans = 0;
  for(int i = 30; i >= 0 && u != -1; i--) {
    int b1 = 0;
    if(x & (1 << i)) b1 = 1;
    int b2 = 0;
    if(k & (1 << i)) b2 = 1;
    if(b2 == 0) {
      if(tr[u][b1 ^ 1] != -1) ans += sz[tr[u][b1 ^ 1]];
      u = tr[u][b1];
    } else {
      u = tr[u][b1 ^ 1];
    }
  }
  if(u != -1) ans += sz[u];
  return ans;
}

int n; ll k;

void solve() {
  scanf("%d%lld", &n, &k);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }

  pt.init();
  for(int i = 1; i <= n; i++) {
    pt.add(i, a[i]);
  }
  
  int l = 0, r = (1 << 30), p = -1;
  while(l <= r) {
    int mid = l + (r - l) / 2;
    ll cnt = 0;
    for(int i = 2; i <= n; i++) {
      cnt += pt.greaterAndEqual(i - 1, a[i], mid);
    }

    if(cnt >= k) {
      p = mid;
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  
  ll ans = 0;
  ll cnt = 0;
  memset(c, 0, sizeof c);
  memset(tr, -1, sizeof tr);
  memset(sz, 0, sizeof sz);

  add(a[1]);
  for(int i = 2; i <= n; i++) {
    ans += query1(a[i], p + 1);
    ans %= MOD;
    cnt += query2(a[i], p + 1);
    add(a[i]);
  }

  ans += ((p + 0ll) * (k - cnt));
  ans %= MOD;
  cout << ans << endl;
}

int main(){
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
