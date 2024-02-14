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

struct node {
  int l, r;
  mutable int v; 
  node(ll l, ll r, ll v) : l(l), r(r), v(v) {} 
  bool operator<(const node &o) const { return l < o.l; } 
};

set<node> tree;
int ans = 0;

auto split(int pos) {
  auto it = tree.lower_bound(node(pos, 0, 0)); 
  if (it != tree.end() && it->l == pos) 
    return it;
  it--; 
  ll l = it -> l, r = it -> r, v = it -> v;
  tree.erase(it); 
  tree.insert(node(l, pos - 1, v)); 
  auto res = tree.insert(node(pos, r, v)).first; 
  
  ans -= (r - l + 1) * v;
  ans += (r - pos + 1) * v;
  ans += ((pos - 1) - l + 1) * v;
  return res;
}

void assign(int l, int r, int v) {
  auto end = split(r + 1), begin = split(l); // 顺序不能颠倒，否则可能RE
  for(auto it = begin; it != end; it++) {
    int l = it -> l, r = it -> r, x = it -> v;
    ans -= (r - l + 1) * x;
  }
  tree.erase(begin, end); 
  tree.insert(node(l, r, v));
  ans += (r - l + 1) * v;
}

void solve() {
  int n, m;
  cin >> n >> m;
  tree.insert({1, n, 1}); // 0: non working day, 1: working day
  ans = n;
  while(m--) {
    int op, l, r;
    scanf("%d%d%d", &l, &r, &op);
    assign(l, r, op - 1);
    printf("%d\n", ans);
  }
  
}

int main() {
  int t = 1;
  while(t--) {
    solve();
  }
  return 0;
}
