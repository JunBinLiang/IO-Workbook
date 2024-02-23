#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>

using namespace std;  

const int N = 2e5 + 10;// M = N;
const int M = 8000005;
vector<int> g1[N], g2[M];
int sz[N], dep[N], fa[N], son[N], top[N];
int ids[N], rids[N], cnt = 0;
int in[M], ans[N];
int n, m;

void add(int a, int b)  // 添加一条边a->b
{
    g2[a].push_back(b);
    in[b]++;
    //cout << "add " << a + 1 << " " << b + 1 << endl;
}

void dfs(int pa, int root, int h) {
  fa[root] = pa;
  sz[root] = 1;
  dep[root] = h;
  
  for(int& nxt : g1[root]) {
    if(nxt == pa) continue;
      dfs(root, nxt, h + 1);
      sz[root] += sz[nxt];
      if(son[root] == -1) {
        son[root] = nxt;
      } else {
        if(sz[nxt] > sz[son[root]]) {
          son[root] = nxt;
        }
    }
  }
}

void dfs1(int pa, int root, int line) {
  top[root] = line;
  ids[root] = cnt++;
  rids[ids[root]] = root;
  if(son[root] == -1) return;
  dfs1(root, son[root], line);
  for(int& nxt : g1[root]) {
    if(nxt == pa || nxt == son[root]) continue;
    dfs1(root, nxt, nxt); //a new heavy line
  }
}

struct node {
  int ls, rs;
} tr[M];

int rt[2], id;
void build(int u, int l, int r, int op) {
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  
  if(l == mid) {
    tr[u].ls = l;
  } else {
    tr[u].ls = id++;
    build(tr[u].ls, l, mid, op);
  }

  if(mid + 1 == r) {
    tr[u].rs = r;
  } else {
    tr[u].rs = id++;
    build(tr[u].rs, mid + 1, r, op);
  }

  if(op == 1) {
    add(u, tr[u].ls);
    add(u, tr[u].rs);
  } else {
    add(tr[u].ls, u);
    add(tr[u].rs, u);
  }
}

void modify(int u, int l, int r, int s, int e, int x, int op) {
  if(l == s && r == e) {
    if(op == 1) {
      add(x, u);
    }
    else {
      add(u, x);
    }
    return;
  }
  int mid = l + (r - l) / 2;
  if(e <= mid) {
    modify(tr[u].ls, l, mid, s, e, x, op);
  } else if(s >= mid + 1) {
    modify(tr[u].rs, mid + 1, r, s, e, x, op);
  } else {
    modify(tr[u].ls, l, mid, s, mid, x, op);
    modify(tr[u].rs, mid + 1, r, mid + 1, e, x, op);
  }
}

void update_path(int u, int v, int x, int op) {
  while(top[u] != top[v]) {
    if(dep[top[u]] < dep[top[v]]) swap(u, v);
      if(ids[top[u]] <= x && x <= ids[u]) {
        if(ids[top[u]] <= x - 1) {
          modify(rt[op], 0, n - 1, ids[top[u]], x - 1, x, op);
        }
        if(x + 1 <= ids[u]) {
          modify(rt[op], 0, n - 1, x + 1, ids[u], x, op);
        }
      } else {
        modify(rt[op], 0, n - 1, ids[top[u]], ids[u], x, op);
      }
      u = fa[top[u]];
  }
    
  //same heave-line
  if(dep[u] < dep[v]) swap(u, v);
  if(ids[v] <= x && x <= ids[u]) {
    if(ids[v] <= x - 1) {
      modify(rt[op], 0, n - 1, ids[v], x - 1, x , op);
    }
    if(x + 1 <= ids[u]) {
      modify(rt[op], 0, n - 1, x + 1, ids[u], x , op);
    }
  } else {
    modify(rt[op], 0, n - 1, ids[v], ids[u], x, op);
  }
}


void solve() {
  scanf("%d%d", &n, &m);
  for(int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--; v--;
    g1[u].push_back(v);
    g1[v].push_back(u);
  }
  
  memset(in, 0, sizeof in);
  memset(son, -1, sizeof son);
  memset(ans, -1, sizeof ans);
  
  id = 1;
  dfs(-1, 0, 0);
  dfs1(-1, 0, 0);

  id = n + 1;
  rt[0] = id++;
  build(rt[0], 0, n - 1, 0);
  rt[1] = id++;
  build(rt[1], 0, n - 1, 1);
  
  //for(int i = 0; i < n; i++) cout << ids[i] << " ";
  //cout << endl;
  //cout << endl;

  for(int i = 0; i < m; i++) {
    int op, u, v, x;
    scanf("%d%d%d%d", &op, &u, &v, &x);
    u--; v--; x--; op--;
    update_path(u, v, ids[x], op);
  }
  
  queue<int> q;
  for(int i = 0; i < id; i++) {
    if(!in[i]) {
      q.push(i);
    }
  }
  
  int ord = 1;
  while(q.size()) {
    int u = q.front(); q.pop();
    if(u < n) {
      ans[rids[u]] = ord++;
    }
        
    for(int i = g2[u].size() - 1; i >= 0; i--) {
      int nxt = g2[u][i];
      in[nxt]--;
      if(in[nxt] == 0) {
        q.push(nxt);
      }
    }    
  }
  
  for(int i = 0; i < n; i++) {
    if(ans[i] == -1) {
      printf("-1");
      return;
    }
  }
  for(int i = 0; i < n; i++) printf("%d ", n - ans[i] + 1);
}

int main(){
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}

