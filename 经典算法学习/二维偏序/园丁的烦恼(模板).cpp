//https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P2163
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

const int SIZE = 1e7 + 100;
struct Fenwick {
  int tree[SIZE];
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

  int pre(int i) {
    int sum = 0;
    while(i>0){
      sum += tree[i];
      i -= ( i & -i);
    }
    return sum;
  }
  int query(int i, int j) {
      return pre(j + 1) - pre(i);
  }
} tr;

struct T {
    int x, y, v, i;
    bool operator < (T& other) {
        return x < other.x;
    }
};

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<pair<int, int>> a;
  vector<T> q;
  vector<int> ans(m);
  for(int i = 0; i < n; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    x++; y++;
    a.push_back({x, y});
  }

  for(int i = 0; i < m; i++) {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    x1++; y1++; x2++; y2++;
    q.push_back({x2, y2, 1, i});
    q.push_back({x1 - 1, y1 - 1, 1, i});
    q.push_back({x1 - 1, y2, -1, i});
    q.push_back({x2, y1 - 1, -1, i});
  }

  sort(a.begin(), a.end());
  sort(q.begin(), q.end());

  int i = 0;
  for(auto& v : q) {
    while(i < n && a[i].first <= v.x) {
      tr.update(a[i].second, 1);
      i++;
    }
    ans[v.i] += (tr.query(0, v.y) * v.v);
  }
  
  for(int i = 0; i < m; i++) {
    printf("%d\n", ans[i]);
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
