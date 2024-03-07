#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
#include <string.h>

using namespace std;  
using ll = long long;

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

//a[n] = 1
//b[n] = n
//c[n] = 1/2 * n * (n + 1)
//d[n] = 1/6 * (n + 1) * (2n + 1) - 1/2 * n^2 * (n + 1)

//n <= m : d[n] * a[m] + c[n] * b[m]
//m > n :  a[n] * d[m] + b[n] * c[m]

int v1(int n) {return 1;}
ll v2(int n) {return n;}
ll v3(int n) {return (n + 0ll) * (n + 1) / 2;}
ll v4(int n) {return (n + 0ll) * (n + 1) * (2 * n + 1) / 6 - (n + 0ll) * n * (n + 1) / 2;}

const int SIZE = 300000 + 100;
struct Fenwick {
  ll tree[SIZE];
  void init(int n) {
    for(int i = 0; i <= n + 1; i++) tree[i] = 0;
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
} tr1[4], tr2[4];

struct node {
  int l, r;
  mutable int v; 
  node(int l, int r,  int v) : l(l), r(r), v(v) {} 
  bool operator<(const node &o) const { return l < o.l; } 
};

set<node> s1, s2;
ll ans = 0;
int n, m, q;

void print(set<node>& s) {
  for(auto it : s) {
    cout << "[ " << it.l << " " << it.r << " " << it.v << "] ";
  }
  cout << endl;
}

vector<pair<int, int>> split(set<node>& s, int pos) {
  vector<pair<int, int>> ans;
  auto it = s.lower_bound(node(pos, 0, 0)); 
  if(it -> l != pos) it--;
  int l = it -> l, r = it -> r, v = it -> v;
  ans.push_back({0, r - l + 1});
  s.erase(it); 
  s.insert({pos, pos, 0});
  if(l <= pos - 1) {
    s.insert({l, pos - 1, v});
    ans.push_back({1, (pos - 1 - l + 1)});
  }
  if(pos + 1 <= r) {
    s.insert({pos + 1, r, v});
    ans.push_back({1, r - (pos + 1) + 1});
  }
  return ans;
}

vector<pair<int, int>> merge(set<node>& s, int pos) {
  vector<pair<int, int>> ans;
  auto it1 = s.lower_bound(node(pos, 0, 0)); 
  auto it2 = s.lower_bound(node(pos, 0, 0)); 
  int l = pos, r = pos;
  it1--;
  if(it1 -> v == 1) {
    l = it1 -> l;
  }
  if(it2 != s.end()) {
    it2++;
    if(it2 -> v == 1) {
      r = it2 -> r;
    }
  }

  while(true) {
    auto it = s.lower_bound(node(l, 0, 0));
    if(it == s.end() || it -> l > r) {
      break;
    } 
    if(it -> v == 1)
        ans.push_back({0, it -> r - it -> l + 1});
    s.erase(it);
  }
  s.insert({l, r, 1});
  ans.push_back({1, r - l + 1});
  return ans;
  
}

void process1(vector<pair<int, int>>& a) {
  for(auto& p : a) {
    int op = p.first, sz = p.second;
    ll x = v4(sz) * tr2[0].query(sz, m) + v3(sz) * tr2[1].query(sz, m);
    ll y = v1(sz) * tr2[3].query(0, sz - 1) + v2(sz) * tr2[2].query(0, sz - 1);
    if(op == 0) { //remove
      tr1[0].update(sz, -v1(sz));
      tr1[1].update(sz, -v2(sz));
      tr1[2].update(sz, -v3(sz));
      tr1[3].update(sz, -v4(sz));
      ans -= (x + y);
    } else { //add
      tr1[0].update(sz, v1(sz));
      tr1[1].update(sz, v2(sz));
      tr1[2].update(sz, v3(sz));
      tr1[3].update(sz, v4(sz));
      ans += (x + y);
    }
  }
}

void process2(vector<pair<int, int>>& a) {
  for(auto& p : a) {
    int op = p.first, sz = p.second;
    ll x = v4(sz) * tr1[0].query(sz, m) + v3(sz) * tr1[1].query(sz, m);
    ll y = v1(sz) * tr1[3].query(0, sz - 1) + v2(sz) * tr1[2].query(0, sz - 1);
    if(op == 0) { //remove
      tr2[0].update(sz, -v1(sz));
      tr2[1].update(sz, -v2(sz));
      tr2[2].update(sz, -v3(sz));
      tr2[3].update(sz, -v4(sz));
      ans -= (x + y);
    } else { //add
      tr2[0].update(sz, v1(sz));
      tr2[1].update(sz, v2(sz));
      tr2[2].update(sz, v3(sz));
      tr2[3].update(sz, v4(sz));
      ans += (x + y);
    }
  }
}

void solve() {
  cin >> n >> m >> q;
  vector<ll> a(n + 1), b(m + 1);
  for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
  for(int i = 1; i <= m; i++) scanf("%lld", &b[i]);
  for(int i = n; i >= 2; i--) a[i] -= a[i - 1];
  for(int i = m; i >= 2; i--) b[i] -= b[i - 1];
  
  s1.insert({2, n, 1});
  s2.insert({2, m, 1});
  for(int i = 2; i <= n; i++) {
      if(a[i] == 0) {
          split(s1, i);
      }
      
  }
  for(int i = 2; i <= m; i++) if(b[i] == 0) split(s2, i);
  

  for(int i = 0; i < 4; i++) {
    tr1[i].init(n + 5);
    tr2[i].init(m + 5);
  }
  
  for(auto it : s2) {
    int l = it.l, r = it.r, v = it.v;
    if(v == 1) {
      int sz = r - l + 1;
      tr2[0].update(sz, v1(sz));
      tr2[1].update(sz, v2(sz));
      tr2[2].update(sz, v3(sz));
      tr2[3].update(sz, v4(sz));
    }
  }

  //n <= m : d[n] * a[m] + c[n] * b[m]
  //m > n :  a[n] * d[m] + b[n] * c[m]
  for(auto it : s1) {
    int l = it.l, r = it.r, v = it.v;
    if(v == 1) {
      int sz = r - l + 1;
      tr1[0].update(sz, v1(sz));
      tr1[1].update(sz, v2(sz));
      tr1[2].update(sz, v3(sz));
      tr1[3].update(sz, v4(sz));
      //n <= m
      ll x = v4(sz) * tr2[0].query(sz, m) + v3(sz) * tr2[1].query(sz, m);
      //n > m
      ll y = v1(sz) * tr2[3].query(0, sz - 1) + v2(sz) * tr2[2].query(0, sz - 1);
      //cout << v4(sz) << " " << tr2[0].query(sz, m) << endl;
      //cout << v3(sz) << " " << tr2[1].query(sz, m) << endl;
      ans += x;
      ans += y;
    }
  }
  
  //print(s1);
  //print(s2);
  
  ans += ((n + 0ll) * m);
  printf("%lld\n", ans);
  
  while(q--) {
    int op, l, r, v;
    scanf("%d%d%d%d", &op, &l, &r, &v);
    if(v == 0) continue;
    if(op == 1) {
      if(l > 1) {
        if(a[l] == 0) {
          vector<pair<int, int>> q = merge(s1, l);
          process1(q);
        }
        a[l] += v;
        if(a[l] == 0) {
          vector<pair<int, int>> q = split(s1, l);
          process1(q);
        }
      }
      if(r + 1 <= n) {
        if(a[r + 1] == 0) {
          vector<pair<int, int>> q = merge(s1, r + 1);
          process1(q);
        }
        a[r + 1] -= v;
        if(a[r + 1] == 0) {
          vector<pair<int, int>> q = split(s1, r + 1);
          process1(q);
        }
      }
    } else {
      if(l > 1) {
        if(b[l] == 0) {
          vector<pair<int, int>> q = merge(s2, l);
          process2(q);
        }
        b[l] += v;
        if(b[l] == 0) {
          vector<pair<int, int>> q = split(s2, l);
          process2(q);
        }
      }
      if(r + 1 <= m) {
        if(b[r + 1] == 0) {
          vector<pair<int, int>> q = merge(s2, r + 1);
          process2(q);
        }
        b[r + 1] -= v;
        if(b[r + 1] == 0) {
          vector<pair<int, int>> q = split(s2, r + 1);
          process2(q);
        }
      }
    }
    printf("%lld\n", ans);
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
