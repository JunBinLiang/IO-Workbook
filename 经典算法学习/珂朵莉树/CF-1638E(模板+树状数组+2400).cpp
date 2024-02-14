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



const int N = 1e6 + 10;
int n, m;
ll add[N];

namespace Fenwick {
  const int SIZE = 1e6 + 100;
  ll tree[SIZE];
  void init() {
    memset(tree, 0, sizeof(tree));
  }

  void update(int i, ll val) {
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
      return pre(j + 1) - pre(i);
  }
}


struct node {
  int l, r;
  mutable int c; 
  node(ll l, ll r, ll c) : l(l), r(r), c(c) {} 
  bool operator<(const node &o) const { return l < o.l; } 
};
set<node> tree;

auto split(int pos) {
  auto it = tree.lower_bound(node(pos, 0, 0)); 
  if (it != tree.end() && it->l == pos) 
    return it;
  it--; 
  ll l = it -> l, r = it -> r, c = it -> c;
  tree.erase(it); 
  tree.insert(node(l, pos - 1, c)); 
  return tree.insert(node(pos, r, c)).first; 
}

void assign(int l, int r, int v) {
  auto end = split(r + 1), begin = split(l); // 顺序不能颠倒，否则可能RE
  for(auto it = begin; it != end; it++) {
      int l = it -> l, r = it -> r, c = it -> c;
      Fenwick :: update(l, add[c]);
      Fenwick :: update(r + 1, -add[c]);
  }
  tree.erase(begin, end); 
  tree.insert(node(l, r, v));
  Fenwick :: update(l, -add[v]);
  Fenwick :: update(r + 1, add[v]);
}


char op[20];
void solve() {
  scanf("%d%d", &n, &m);
  memset(add, 0, sizeof add);
  tree.insert({1, n, 1});
  Fenwick :: init();
  
  for(int i = 0; i < m; i++) {
    scanf("%s", op);
    if(op[0] == 'C') {
      int l, r, c;
      scanf("%d%d%d", &l, &r, &c);
      assign(l, r, c);
    } else if(op[0] == 'A') {
      int c, x;
      scanf("%d%d", &c, &x);
      add[c] += x;
    } else {
      int idx;
      scanf("%d", &idx);
      auto it = split(idx);
      ll ans = Fenwick :: query(1, idx) + add[it -> c];
      printf("%lld\n", ans);
    }
  }
}


int main() {
  int t = 1;
  while(t--) {
    solve();
  }
  return 0;
}
