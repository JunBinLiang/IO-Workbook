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

const int N = 5e5 + 10;
int p[N];
int find(int u) {
  return p[u] == u ? u : p[u] = find(p[u]);
}

struct Segment {
  int l, r, w;
  bool operator<(Segment& other) {
    return l < other.l;
  }
};

struct E {
  int u, v, w;
  bool operator<(E& other) {
    return w < other.w;
  }
};

void solve() {
  int n;
  scanf("%d", &n);
  for(int i = 0; i <= n; i++) p[i] = i;

  vector<Segment> a;
  for(int i = 0; i < n; i++) {
    int l, r, w;
    scanf("%d%d%d", &l, &r, &w);
    a.push_back({l, r, w});
  }

  sort(a.begin(), a.end());
  vector<E> e;
  set<pair<int, int>> s1, s2;
  for(int i = 0; i < n; i++) {
    int l = a[i].l, r = a[i].r, w = a[i].w;
    while(s1.size() > 0) {
      auto it = s1.begin();
      int prer = it -> first, index = it -> second;
      if(prer < l) {
        s1.erase({prer, index});
        s2.erase({a[index].w, index});
      } else {
        break;
      }
    }
    if(s2.size() > 0) {
      auto it = s2.upper_bound({w, -1});
      if(it != s2.end()) {
        int index = it -> second;
        e.push_back({index, i, abs(it -> first - w)});
      }
      if(it != s2.begin()) {
        it--;
        int index = it -> second;
        e.push_back({index, i, abs(it -> first - w)});
      }
    }

    s1.insert({r, i});
    s2.insert({w, i});
  }

  //MST
  sort(e.begin(), e.end());
  ll ans = 0, cnt = 0;
  for(int i = 0; i < e.size(); i++) {
    int u = e[i].u, v = e[i].v;
    int r1 = find(u), r2 = find(v);
    if(r1 != r2) {
      cnt++;
      ans += e[i].w;
      p[r1] = r2;
    }
  }
  if(cnt + 1 != n) printf("-1\n");
  else printf("%lld\n", ans);
} 

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
