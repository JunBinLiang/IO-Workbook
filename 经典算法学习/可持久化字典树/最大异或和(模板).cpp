//https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P4735
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

const int N = 6e5 + 10;
struct PersistantTrie {
  int roots[N];
  int tr[N * 28][2];
  int cnt[N * 28 * 2];
  int id;

  void init() {
    memset(tr, -1, sizeof tr);
    memset(cnt, 0, sizeof cnt);
    roots[0] = 0;
    id = 1;
  }

  void add(int ith, int x) {
    roots[ith] = id++;
    int pu = roots[ith - 1], u = roots[ith];
    for(int i = 27; i >= 0; i--) {
      int b = 0;
      if(x & (1 << i)) b = 1;
      if(pu == -1) {
        tr[u][b] = id++;
        u = tr[u][b];
        cnt[u] = 1;
      } else {
        if(tr[pu][b] == -1) {
          tr[u][b] = id++;
          tr[u][b ^ 1] = tr[pu][b ^ 1];
          u = tr[u][b];
          pu = -1;
          cnt[u] = 1;
        } else {
          tr[u][b] = id++;
          tr[u][b ^ 1] = tr[pu][b ^ 1];
          u = tr[u][b];
          pu = tr[pu][b];
          cnt[u] = 1 + cnt[pu];
        }
      }
    }
  }

  int query(int l, int r, int x) {
    int ans = 0;
    int pu = roots[l - 1], u = roots[r];
    for(int i = 27; i >= 0; i--) {
      int b = 0;
      if(x & (1 << i)) b = 1;
      if(pu == -1) {
        if(tr[u][b ^ 1] != -1) {
          u = tr[u][b ^ 1];
          ans += (1 << i);
        } else {
          u = tr[u][b];
        }
      } else {
        if(tr[u][b ^ 1] != -1) {
          if(tr[pu][b ^ 1] != -1) {
            if(cnt[tr[u][b ^ 1]] - cnt[tr[pu][b ^ 1]] > 0) {
              u = tr[u][b ^ 1];
              pu = tr[pu][b ^ 1];
              ans += (1 << i);
            } else {
              u = tr[u][b];
              pu = tr[pu][b];
            }
          } else {
            pu = -1;
            u = tr[u][b ^ 1];
            ans += (1 << i);
          }
        } else {
          u = tr[u][b];
          pu = tr[pu][b];
        }
      }
    }
    return ans;
  } 
} pt;

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  pt.init();
  pt.add(0, 0);
  int xo = 0;
  for(int i = 1; i <= n; i++) {
    int x;
    scanf("%d", &x);
    xo ^= x;
    pt.add(i, xo);
  }

  int index = n + 1;
  for(int i = 0; i < m; i++) {
    char op[2];
    scanf("%s", op);
    if(op[0] == 'A') {
      int x;
      scanf("%d", &x);
      xo ^= x;
      pt.add(index, xo);
      index++;
    } else {
      int L, R, x;
      scanf("%d%d%d", &L, &R, &x);
      int ans = pt.query(L - 1, R - 1, x ^ xo);
      printf("%d\n", ans);
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

