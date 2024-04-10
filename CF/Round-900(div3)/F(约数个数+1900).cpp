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

const int N = 1e6 + 5;
void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  unordered_map<int, int> f, g;
  int cur = n;
  for(int i = 2; i * i <= cur; i++) {
    if(cur % i == 0) {
      while(cur % i == 0) {
        cur /= i;
        f[i]++;
        g[i]++;
      }
    }
  }

  if(cur > 1) {
    f[cur]++;
    g[cur]++;
  }


  while(m--) {
    int op;
    scanf("%d", &op);
    if(op == 1) {
      int v;
      scanf("%d", &v);
      for(int i = 2; i * i <= v; i++) {
        if(v % i == 0) {
          while(v % i == 0) {
            v /= i;
            g[i]++;
          }
        }
      }
      if(v > 1) g[v]++;
      int t = 1;
      for(auto it = g.begin(); it != g.end(); it++) {
        int c = it -> second + 1;
        t *= c;
      }

      bool ok = true;
      for(auto it = g.begin(); it != g.end(); it++) {
        int v = it -> first, c = it -> second;
        while(t % v == 0 && c > 0) t /= v, c--;
      }
      if(t == 1) printf("YES\n");
      else printf("NO\n");
    } else {
      g.clear();
      for(auto it = f.begin(); it != f.end(); it++) {
        g[it -> first] = it -> second;
      }
    }
  }

  printf("\n");
}


int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
