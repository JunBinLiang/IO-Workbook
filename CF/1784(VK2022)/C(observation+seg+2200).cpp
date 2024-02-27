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
ostream &operator<<(ostream &out, const set<T> &a)
{
  out << "[";
  bool first = true;
  for (auto v : a)
  {
    out << (first ? "" : ", ");
    out << v;
    first = 0;
  }
  out << "]";
  return out;
}

const int N = 200000 + 100;
const int INF = 1e9;
int id  = 1; int n;

ll ans[N];
int rk[N], rrk[N];

struct Node {
  int ls, rs, val, sz, addtag, mn;
} tr[N * 4];

void build(int u, int l, int r) {
  if(l == r) return;
  int mid = l + (r - l) / 2;
  int ls = id++, rs = id++;
  tr[u].ls = ls, tr[u].rs = rs;
  tr[ls] = {0, 0, INF, 0, 0, INF};
  tr[rs] = {0, 0, INF, 0, 0, INF};
  build(ls, l, mid);
  build(rs, mid + 1, r);
}

void pushdown(int u) {
  if(tr[u].ls != 0 && tr[u].rs != 0 && tr[u].addtag != 0) {
    int ls = tr[u].ls, rs = tr[u].rs;
    tr[ls].addtag += tr[u].addtag;
    tr[ls].mn += tr[u].addtag;
    tr[rs].addtag += tr[u].addtag;
    tr[rs].mn += tr[u].addtag;
    tr[ls].mn = max(0, tr[ls].mn);
    tr[rs].mn = max(0, tr[rs].mn);
    tr[u].addtag = 0;
  }
}

void pushup(int u) {
  if(tr[u].ls != 0 && tr[u].rs != 0) {
    int ls = tr[u].ls, rs = tr[u].rs;
    tr[u].sz = tr[ls].sz + tr[rs].sz;
    tr[u].mn = min(tr[ls].mn, tr[rs].mn);
  }
}

void modify(int u, int l, int r, int s, int e, int x, int op) {
  if(l == s && r == e) {
    if(op == 0) {
      tr[u].addtag += x;
      tr[u].mn += x;
      tr[u].mn = max(0, tr[u].mn);
    } else {
      tr[u].val = tr[u].mn = x;
      tr[u].sz = 1;
      tr[u].addtag = 0;
      //cout << "yes " << l << " " << r << " " << u << " " << tr[u].val <<" " << tr[u].addtag << endl;
    }
    return;
  }
  int mid = l + (r - l) / 2;
  pushdown(u);
  if(e <= mid) {
    modify(tr[u].ls, l, mid, s, e, x, op);
  } else if(s >= mid + 1) {
    modify(tr[u].rs, mid + 1, r, s, e, x, op);
  } else {
    modify(tr[u].ls, l, mid, s, mid, x, op);
    modify(tr[u].rs, mid + 1, r, mid + 1, e, x, op);
  }
  pushup(u);
}

int query1(int u, int l, int r, int s, int e) { // query sum from [0 : l]
  if(l == s && r == e){
    return tr[u].sz;
  }
  pushdown(u);
  int mid = l + (r - l) / 2;
  int left = tr[u].ls, right = tr[u].rs;
  if(e <= mid){
      return query1(left, l, mid, s, e);
  } else if(s >= mid + 1) {
      return query1(right, mid + 1, r, s, e);
  } else {
    return query1(left, l, mid, s, mid) + query1(right, mid + 1, r, mid + 1, e);
  }
}

int query2(int u, int l, int r, int idx) { // query sum from [0 : l]
  if(l == r){
    return tr[u].mn;
  }
  pushdown(u);
  int mid = l + (r - l) / 2;
  int left = tr[u].ls, right = tr[u].rs;
  if(idx <= mid){
      return query2(left, l, mid, idx);
  } else {
      return query2(right, mid + 1, r, idx);
  }
}

int query3(int u, int l, int r, int s, int e) { // query sum from [0 : l]
  if(l == s && r == e){
    return tr[u].mn;
  }
  pushdown(u);
  int mid = l + (r - l) / 2;
  int left = tr[u].ls, right = tr[u].rs;
  if(e <= mid){
      return query3(left, l, mid, s, e);
  } else if(s >= mid + 1) {
      return query3(right, mid + 1, r, s, e);
  } else {
    return min(query3(left, l, mid, s, mid), query3(right, mid + 1, r, mid + 1, e));
  }
}

int dfs(int u, int l, int r, int pos) {
  int ls = tr[u].ls, rs = tr[u].rs;
  if(l == r) {
    return l;
  }

  int mid = l + (r - l) / 2;
  if(pos <= mid) {
    if(query3(0, 1, n + 1, pos, mid) != 0) {
      return dfs(rs, mid + 1, r, pos);
    } else {
      return dfs(ls, l, mid, pos);
    }
  } else {
    return dfs(rs, mid + 1, r, pos);
  }
}


void solve() {
  scanf("%d", &n);
  vector<int> a(n + 1);
  vector<pair<int, int>> b;
  for(int i = 1; i <= n; i++) {
    cin >> a[i];
    b.push_back({a[i], i});
  }
  
  sort(b.begin(), b.end());
  for(int i = 0; i < b.size(); i++) {
    rk[b[i].second] = i + 1;
    rrk[i + 1] = b[i].second;
  }

  id = 1;
  tr[0] = {0, 0, INF, 0, 0, INF};
  build(0, 1, n + 1);

  ll sum = 0;
  set<int> s;
  for(int i = 1; i <= n; i++) {
    int pos = rk[i];
    auto it = s.upper_bound(pos);
    int to = 0;
    
    if(it != s.begin()) {
      it--;
      int prepos = *it;
      to = a[rrk[prepos]] - query2(0, 1, n + 1, prepos);
    } 
    bool change = false;
    if(to + 1 <= a[i]) {
        to++;
        change = true;
    }
    
    modify(0, 1, n + 1, pos, pos, a[i] - to, 1);
    sum += (a[i] - to);
    
    if(change) {
      if(query3(0, 1, n + 1, pos + 1, n + 1) == 0) { //there is 0
        int nxtpos = dfs(0, 1, n + 1, pos + 1);
        
        if(pos + 1 <= nxtpos - 1) {
          modify(0, 1, n + 1, pos + 1, nxtpos - 1, -1, 0);
          sum -= query1(0, 1, n + 1, pos + 1, nxtpos - 1);
        }
      } else { //whole update
        modify(0, 1, n + 1, pos + 1, n + 1, -1, 0);
        sum -= query1(0, 1, n + 1, pos + 1, n + 1);
      }
    }
    
    //cout << endl;
    s.insert(pos);
    ans[i] = sum;
  }
  for(int i = 1; i <= n; i++) {
    printf("%lld ", ans[i]);
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


