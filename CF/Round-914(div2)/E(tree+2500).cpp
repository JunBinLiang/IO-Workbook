#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;  

const int MAX = 2e5 + 10;
struct Node {
  int l, r;
  int tag = 0, mx = 0;
} tr[MAX * 4];

void pushup(int u) {
  int lid = u * 2 + 1, rid = u * 2 + 2;
  if(tr[u].l != tr[u].r) {
    tr[u].mx = max(tr[lid].mx, tr[rid].mx);
  }
}

void pushdown(int u) {
  if(tr[u].tag) {
    int lid = u * 2 + 1, rid = u * 2 + 2;
    if(tr[u].l != tr[u].r) {
      tr[lid].tag += tr[u].tag;
      tr[rid].tag += tr[u].tag;
      tr[lid].mx += tr[u].tag;
      tr[rid].mx += tr[u].tag;
    }
    tr[u].tag = 0;
  }
}

void build(int id) {
  int l = tr[id].l, r = tr[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tr[id * 2 + 1] = {l, mid, 0, 0};
  tr[id * 2 + 2] = {mid + 1, r, 0, 0};
  build(id * 2 + 1);
  build(id * 2 + 2);
}

void update(int id, int s, int e, int val) { 
  int l = tr[id].l, r = tr[id].r;
  if(l == s && r == e) {
    tr[id].tag += val;
    tr[id].mx += val; 
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  pushdown(id);
  if(e <= mid) {
    update(left, s, e, val);
  } else if(s >= mid + 1) {
    update(right, s, e, val);
  } else {
    update(left, s, mid, val);
    update(right, mid + 1, e, val);
  }
  pushup(id);
}

int query(int id, int s, int e) { // query sum from [0 : l]
  int l = tr[id].l, r = tr[id].r;
  if(l == s && r == e){
    return tr[id].mx;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  pushdown(id);
  if(e <= mid){
      return query(left, s, e);
  } else if(s >= mid + 1) {
      return query(right, s, e);
  } else {
    return max(query(left, s, mid), query(right, mid + 1, e));
  }
}

void dfs(int u) {
    int lid = u * 2 + 1, rid = u * 2 + 2;
    cout << tr[u].l << " " << tr[u].r << "  " << tr[u].mx << endl;
    if(tr[u].l == tr[u].r) return;
    dfs(lid);
    dfs(rid);
}



const int N = 2e5 + 100;
vector<int> g[N];
vector<vector<int>> q[N];
int sz[N], ids[N], ans[N], h[N], id = 1;
int f[20][N];
int n, m;

int jump(int u, int t) {
    for(int i = 19; i >= 0; i--) {
        if(t & (1 << i)) u = f[i][u];
    }
    return u;
}

void dfs1(int pa, int u) {
  ids[u] = id++;
  sz[u] = 1;
  if(pa != -1) h[u] = 1 + h[pa];
  f[0][u] = pa;
  for(int nxt : g[u]) {
    if(pa != nxt) {
      dfs1(u, nxt);
      sz[u] += sz[nxt];
    }
  }
}

void dfs2(int pa, int u) {
  int l = ids[u], r = l + sz[u] - 1;
  if(pa != -1) {
    update(1, l, r, -1);
    if(1 <= l - 1) update(1, 1, l - 1, 1);
    if(r + 1 <= n) update(1, r + 1, n, 1);
  }

  for(auto& v : q[u]) {
    int j = v.back();
    int maxH = -1;
    int index = -1;
    int rangeL = 1, rangeR = n;
    for(int i = 0; i < (int)v.size() - 1; i++) {
      int L = ids[v[i]], R = L + sz[v[i]] - 1;
      if(L <= l && R >= r) { //ancestor
        if(h[v[i]] > maxH) {
          maxH = h[v[i]];
          index = i;
        }
      }
    }
    
    if(index != -1) {
        int uu = jump(u, h[u] - maxH - 1);
        rangeL = ids[uu], rangeR = ids[uu] + sz[uu] - 1;
        //cout << uu <<"  " << minH << endl;
    }
    
    //cout << rangeL << " " << rangeR << endl;
    
    vector<pair<int, int>> in;
    for(int i = 0; i < v.size() - 1; i++) {
      if(i == index) continue;
      int L = ids[v[i]], R = L + sz[v[i]] - 1;
      if(rangeL <= L && rangeR >= R) {
        in.push_back({L, R});
      }
    } 

    sort(in.begin(), in.end()); //merge all intervals
    
    vector<pair<int, int>> stk;
    for(int i = 0; i < in.size(); i++) {
      if(stk.size() == 0 || in[i].first > stk.back().second + 1) stk.push_back(in[i]);
      else {
        stk.back().second = max(stk.back().second, in[i].second);
      } 
    }
    
    if(stk.size() > 0) {
      if(rangeL <= stk[0].first - 1) {
        ans[j] = max(ans[j], query(1, rangeL, stk[0].first - 1));
      }
      
      if(stk.back().second + 1 <= rangeR) {
        ans[j] = max(ans[j], query(1, stk.back().second + 1, rangeR));
      }

      for(int i = 1; i < stk.size(); i++) {
        ans[j] = max(ans[j], query(1, stk[i - 1].second + 1, stk[i].first - 1));
      }
    } else {
        ans[j] = query(1, rangeL, rangeR);
    }

  }

  for(int nxt : g[u]) {
    if(nxt == pa) continue;
    dfs2(u, nxt);
  }

  if(pa != -1) {
    update(1, l, r, 1);
    if(1 <= l - 1) update(1, 1, l - 1, -1);
    if(r + 1 <= n) update(1, r + 1, n, -1);
  }
}

void solve() {
  scanf("%d%d", &n, &m);
  for(int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }

  for(int i = 0; i < m; i++) {
    int x, k;
    scanf("%d%d", &x, &k);
    vector<int> query(k);
    for(int j = 0; j < k; j++) {
      scanf("%d", &query[j]);
    }
    query.push_back(i);
    q[x].push_back(query);
  }

  memset(f, -1, sizeof f);
  h[1] = 0;
  dfs1(-1, 1);
  
  for(int i = 1; i < 20; i++) {
    for(int j = 1; j <= n; j++) {
        if(f[i - 1][j] != -1) {
            f[i][j] = f[i - 1][f[i - 1][j]];
        }
            
    }
  }
  
  
  //for(int i = 1; i <= n; i++) cout << ids[i] << " ";
  //cout << endl;
  //for(int i = 1; i <= n; i++) cout << sz[i] << " ";
  //cout << endl;
  
  tr[1] = {1, n, 0, 0};
  build(1);
  for(int i = 1; i <= n; i++) {
    update(1, ids[i], ids[i],  h[i]);
  }
  
  //for(int i = 1; i <= n; i++) cout << query(1, i, i) << " ";
  //cout << endl << endl << endl;
  
  dfs2(-1, 1);

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

