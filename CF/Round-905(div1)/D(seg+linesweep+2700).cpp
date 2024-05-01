#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector


const int MAX = 3e5 + 100;

struct Node {
  int l, r;
  int mn, mx;
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, 500000, -500000};
  tree[id * 2 + 2] = {mid + 1, r, 500000, -500000};
  build(id * 2 + 1);
  build(id * 2 + 2);
}

void update(int id, int index, int val) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    tree[id].mn = min(tree[id].mn, val); 
    tree[id].mx = max(tree[id].mx, val); 
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(index <= mid) {
    update(left, index, val);
  } else {
    update(right, index, val);
  }
  tree[id].mn = min(tree[left].mn, tree[right].mn);
  tree[id].mx = max(tree[left].mx, tree[right].mx);
}

int query1(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].mn;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query1(left, s, e);
  } else if(s >= mid + 1) {
      return query1(right, s, e);
  } else {
    return min(query1(left, s, mid), query1(right, mid + 1, e));
  }
}

int query2(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].mx;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query2(left, s, e);
  } else if(s >= mid + 1) {
      return query2(right, s, e);
  } else {
    return max(query2(left, s, mid), query2(right, mid + 1, e));
  }
}

const int SIZE = 3e5 + 100;
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
} tr1;

const int N = 3e5 + 10;
int a[N];
bool ans[N];
vector<pair<int, int>> add[N], rem[N];

struct Q {
  int l, r, i;
  bool operator<(const Q& other) {
    return l < other.l;
  }
} q[N];

void solve() {
  int n, m;
  scanf("%d", &n);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }

  memset(ans, 0, sizeof ans);
  tree[0] = {1, n, 500000, -500000};
  build(0);
  tr1.init(n + 5);
  for(int i = 1; i <= n; i++) {
    update(0, i, a[i]);
  }

  vector<int> L(n + 1, -1), R(n + 1, -1);
  vector<int> stk;
  for(int i = 1; i <= n; i++) {
    while(stk.size() > 0 && a[i] > a[stk.back()]) {
      R[stk.back()] = i;
      stk.pop_back();
    }
    stk.push_back(i);
  }

  stk.clear();
  for(int i = n; i >= 1; i--) {
    while(stk.size() > 0 && a[i] > a[stk.back()]) {
      L[stk.back()] = i;
      stk.pop_back();
    }
    stk.push_back(i);
  }


  for(int i = 1; i <= n; i++) {
    if(R[i] == -1) continue;
    int l1 = 1, r1 = i;
    if(L[i] != -1) l1 = L[i] + 1;
    int l = R[i], r = n;
    int l2 = R[i], r2 = -1;
    while(l <= r) {
      int mid = l + (r - l) / 2;
      if(query1(0, l2, mid) > a[i]) {
        r2 = mid;
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    add[l1].push_back({l2, r2});
    rem[r1 + 1].push_back({l2, r2});
    //cout << i << "     :" << l1 << " " << r1 << "  " << l2 << " " << r2 << endl;
  }

  scanf("%d", &m);
  for(int i = 0; i < m; i++) {
    scanf("%d%d", &q[i].l, &q[i].r);
    q[i].i = i;
  }
  sort(q, q + m);
  int j = 0;
  for(int i = 1; i <= n; i++) {
    for(auto& p : add[i]) {
      int l = p.first, r = p.second;
      tr1.update(l, 1);
      tr1.update(r + 1, -1);
    }

    for(auto& p : rem[i]) {
      int l = p.first, r = p.second;
      tr1.update(l, -1);
      tr1.update(r + 1, 1);
    }

    while(j < m && q[j].l <= i) {
      if(q[j].l == i) {
        int r = q[j].r;
        if(tr1.query(0, r) > 0) {
          ans[q[j].i] = true;
        }
      }
      j++;
    }
  }

  for(int i = 0; i < m; i++) {
    if(ans[i]) printf("YES\n");
    else printf("NO\n");
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

