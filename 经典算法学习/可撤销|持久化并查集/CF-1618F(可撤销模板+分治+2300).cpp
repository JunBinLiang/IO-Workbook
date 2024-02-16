#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <list>
#include<fstream>
#include <bitset>

using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define P pair
#define V vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define FFOR(i, a, b) for (int i = a; i <= b; ++i)

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

const int N = 5e5 + 10;
vector<pair<int, int>> e[N];
ll res = 0;

//DSU
struct Node {
    int fax, fay, w, sz;
};
vector<Node> stk;
int p[N], rk[N], sz[N]; 
int find(int x) {
    if (p[x] != x) return find(p[x]);
    return p[x];
}

bool merge(int u, int v) {
  int fax = find(u), fay = find(v);
  if(rk[fax] > rk[fay]) {
    swap(fax, fay);
  }
  if(fax != fay) {
    p[fax] = fay;
    sz[fay] += sz[fax];
    stk.push_back({fax, fay, rk[fax] == rk[fay], sz[fax]});
    if(rk[fay] == rk[fax]) rk[fay]++;
    return true;
  }
  return false;
}

void undo(int k) {
  while(k--) {
    auto pa = stk.back(); stk.pop_back();
    int fax = pa.fax, fay = pa.fay, w = pa.w, size = pa.sz;
    p[fax] = fax;
    rk[fay] -= w;
    sz[fay] -= size;
  }
}

void divide(int l, int r) {
  if(l == r) {
    for(auto& p : e[l]) {
      int u = p.first, v = p.second;
      int r1 = find(u), r2 = find(v);
      res += (sz[r1] + 0ll) * (sz[r2]);
    }
    return;
  }
  
  int mid = l + (r - l) / 2;

  int k = 0;
  for(int i = l; i <= mid; i++) {
    for(auto& p : e[i]) {
      int u = p.first, v = p.second;
      if(merge(u, v)) {
        k++;
      }
    }
  }
  
  divide(mid + 1, r);
  undo(k);

  k = 0;
  for(int i = mid + 1; i <= r; i++) {
    for(auto& p : e[i]) {
      int u = p.first, v = p.second;
      if(merge(u, v)) {
        k++;
      }
    }
  }
  
  divide(l, mid);
  undo(k);
}

void solve() {
  int n;
  scanf("%d", &n);
  for(int i = 0; i < n - 1; i++) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    e[w].push_back({u, v});
  }

  memset(rk, 0, sizeof rk);
  for(int i = 0; i < N; i++) {
    p[i] = i;
    sz[i] = 1;
  }

  divide(1, n);

  cout << res << endl;
}

int main() {
  int t = 1;
  while(t--) {
    solve();
  }
  return 0;
}
