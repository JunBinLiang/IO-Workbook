#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)


const int MAX = 1e5 + 100;
const int N = 1e5 + 10;

struct Node {
  int l, r;
  int s;
} tr[N * 4];

void build(int id) {
  int l = tr[id].l, r = tr[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tr[id * 2 + 1] = {l, mid, 0};
  tr[id * 2 + 2] = {mid + 1, r, 0};
  build(id * 2 + 1);
  build(id * 2 + 2);
}
void update(int id, int index, int val) { 
  int l = tr[id].l, r = tr[id].r;
  if(l == r) {
    tr[id].s += val;
    return;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(index <= mid) {
    update(left, index, val);
  } else {
    update(right, index, val);
  }
  tr[id].s = tr[left].s + tr[right].s;
}
int query(int id, int s, int e) {
  int l = tr[id].l, r = tr[id].r;
  if(l == s && r == e){
    return tr[id].s;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query(left, s, e);
  } else if(s >= mid + 1) {
      return query(right, s, e);
  } else {
    return query(left, s, mid) + query(right, mid + 1, e);
  }
}


int findk(int u, int k) {
  if(tr[u].l == tr[u].r) {
    return tr[u].l;
  }
  int left = u * 2 + 1, right = u * 2 + 2;
  if(tr[left].s >= k) {
    return findk(left, k);
  } else {
    return findk(right, k - tr[left].s);
  }
}


//主席树求区间k大
struct pnode {
  int l, r;
  int lid, rid;
  int s;
} ptr[N * 16 * 4];
int roots[N];
int pidx = 1;
void pbuild(int id) {
  int l = ptr[id].l, r = ptr[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  int idx1 = pidx;
  int idx2 = pidx + 1;
  pidx += 2;
  ptr[id].lid = idx1;
  ptr[id].rid = idx2;
  ptr[idx1] = {l, mid, -1, -1, 0};
  ptr[idx2] = {mid + 1, r, -1, -1, 0};
  pbuild(idx1);
  pbuild(idx2);
}

void pupdate(int preId, int curId, int index, int val) {
  int l = ptr[curId].l, r = ptr[curId].r;
  if(l == r) {
    ptr[curId].s = val;
    return;
  }
  int mid = l + (r - l) / 2;
  if (index <= mid) {//update left
    ptr[curId].rid = ptr[preId].rid;
    ptr[pidx] = {ptr[ptr[preId].lid].l, ptr[ptr[preId].lid].r, -1, -1, 0};
    ptr[curId].lid = pidx;
    pidx++;
    pupdate(ptr[preId].lid, ptr[curId].lid, index, val);
  } else {//update right
    ptr[curId].lid = ptr[preId].lid;    
    ptr[pidx] = {ptr[ptr[preId].rid].l, ptr[ptr[preId].rid].r, -1, -1, 0};
    ptr[curId].rid = pidx;
    pidx++;
    pupdate(ptr[preId].rid, ptr[curId].rid, index, val);
  }
  ptr[curId].s = ptr[ptr[curId].lid].s +  ptr[ptr[curId].rid].s;
}

int pquery(int id, int s, int e) {
  int l = ptr[id].l, r = ptr[id].r;
  if(l == s && r == e){
    return ptr[id].s;
  }
  int mid = l + (r - l) / 2;
  int left = ptr[id].lid, right = ptr[id].rid;
  if(e <= mid){
      return pquery(left, s, e);
  } else if(s >= mid + 1) {
      return pquery(right, s, e);
  } else {
    return pquery(left, s, mid) + pquery(right, mid + 1, e);
  }
}


vector<int> g[N];
ll ans[N];
int sz[N], f[N][20], dep[N], ids[N];
int id = 1;
vector<pair<int, int>> q[N];
int n, m;

int to(int u, int k) {
  for(int i = 19; i >= 0; i--) {
    if(k & (1 << i)) {
      u = f[u][i];
    }
  }
  return u;
}

void dfs1(int u, int h) {
  sz[u] = 1;
  dep[u] = h;
  ids[u] = id++;
  for(int v : g[u]) {
    dfs1(v, h + 1);
    sz[u] += sz[v];
  }
}

void dfs2(int u) {
  update(0, u, sz[u]);
  
  for(auto& p : q[u]) {
    int kth = p.first, index = p.second;
    int ancestor = findk(0, kth);
    kth -= query(0, 0, ancestor - 1);
    
    int y = -1;
    if(u != ancestor) {
      int l = 1, r = n;
      int L = ids[ancestor], R = L + sz[ancestor] - 1;
      int v = to(u, abs(dep[ancestor] - dep[u]) - 1);
      int LL  = ids[v], RR = LL + sz[v] - 1;
      while(l <= r) {
        int mid = l + (r - l) / 2;
        int s = pquery(roots[mid], L, R);
        s -= pquery(roots[mid], LL, RR);
        if(s >= kth) {
          y = mid;
          r = mid - 1;
        } else {
          l = mid + 1;
        }
      }
    } else {
      int L = ids[u], R = L + sz[u] - 1;
      int l = 1, r = n;
      while(l <= r) {
        int mid = l + (r - l) / 2;
        int s = pquery(roots[mid], L, R);
        if(s >= kth) {
          y = mid;
          r = mid - 1;
        } else {
          l = mid + 1;
        }
      }
    }
    ans[index] = (u - 1ll) * n * n + (ancestor - 1ll) * n + (y - 1); 
  }
  for(int v : g[u]) {
    update(0, u, -sz[v]);
    dfs2(v);
    update(0, u, sz[v]);
  }
  update(0, u, -sz[u]);
}

void solve() {
  scanf("%d%d", &n, &m);
  int root = -1;
  memset(f, -1, sizeof f);
  
  for(int i = 1; i <= n; i++) {
    int p;
    scanf("%d", &p);
    if(!p) {
      root = i;
    } else {
      f[i][0] = p;
      g[p].push_back(i);
    }
  }

  for(int i = 1; i < 20; i++) {
    for(int u = 1; u <= n; u++) {
      if(f[u][i - 1] != -1) {
        f[u][i] = f[f[u][i - 1]][i - 1];
      }
    }
  }
  
  for(int i = 0; i < m; i++) {
    ll k;
    scanf("%lld", &k);
    int node = (int)(k / n + 1);
    if(k % n == 0) node--;
    int ith = (int)(k % n);
    if(ith == 0) ith += n;
    q[node].push_back({ith, i});
  }

  tr[0] = {0, n, 0};
  build(0);

  dfs1(root, 0);
  
  ptr[0] = {1, n, -1, -1, 0};
  roots[0] = 0;
  pbuild(0);
  for(int i = 1; i <= n; i++) {
    roots[i] = pidx;
    ptr[pidx] = {1, n, -1, -1, 0};
    pidx++;
    pupdate(roots[i - 1], roots[i], ids[i], 1);
  }
  
  dfs2(root);

  for(int i = 0; i < m; i++) {
    printf("%lld\n", ans[i]);
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

