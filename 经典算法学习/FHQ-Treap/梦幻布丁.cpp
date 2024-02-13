//https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P3201
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


unsigned long long seed = 1;
const int N = 3e5 + 10;

struct FHQ {
    struct {
      int l, r;  // 左右孩子
      int val;   // 节点权值
      int rnd;   // 随机值
      int sz;  // 子树大小
      int mx;
    } tr[N];
    
    int gctop = -1, stk[N];
    void gc(int u) {
      if(!u) return;
      stk[++gctop] = u;
      gc(tr[u].l);
      gc(tr[u].r);
    }

    int n = 0;   
    inline int _rand() {
        seed *= 260817;
        return int(seed);
    }

    // 创建一个新节点
    int newnode(int v) {
      int id = -1;
      if(gctop >= 0) {
        id = stk[gctop--];
      } else {
        id = ++n;
      }
      tr[id].val =  v;
      tr[id].rnd = _rand();
      tr[id].sz = 1;
      tr[id].l = tr[id].r = 0;
      return id;
    }

  void pushup(int p) { 
    tr[p].sz = tr[tr[p].l].sz + tr[tr[p].r].sz + 1; 
  }

  void pushdown(int p) {}

  //split by value
  void split(int p, int v, int &x, int &y) {
    if (!p) {  // 空树
      x = y = 0;
      return;
    }
    pushdown(p);
    if (tr[p].val <= v) {
      // 递归分裂 p 的右子树
      // 左子树的根 x 已确定, y 需要继续向下带
      // 同时, p 的右节点需要指向下一层指向的左子树的根 x
      x = p;
      split(tr[p].r, v, tr[p].r, y);
    } else {  // 递归分裂 p 的左子树
      y = p;
      split(tr[p].l, v, x, tr[p].l);
    }
    // 最后, 向上更新每个子树的大小
    pushup(p);
  }


  // 按堆的随机值合并两颗子树, 返回合并后的根
  // 要求 x 树所有节点的 val 要 <= y 树所有节点的 val 值
  int merge(int x, int y) {
    if (!x || !y) return x + y;  // 存在空树的情况
    if (tr[x].rnd < tr[y].rnd) {
      // 应把 x 放上面, 先递归合并 x 的右子树 r 和 y 得到新树 z
      // 因为 x 权值更小, 所以把 z 作为 x 的右孩子
      pushdown(x);
      tr[x].r = merge(tr[x].r, y);
      pushup(x);
      return x;
    } else {
      pushdown(y);
      tr[y].l = merge(x, tr[y].l);
      pushup(y);
      return y;
    }
  }

  int insert(int root, int v) {
    // 按 v 分裂, 找到插入点 x <=v < y
    int x, y;
    split(root, v, x, y);
    // 新建节点
    int z = newnode(v);
    // 依次合并 x, z 和 y (权值 val 也满足如此顺序)
    return merge(merge(x, z), y);
  }
  
  void dfscheck(int u) {
    if(!u) return;
    cout <<"check " <<  tr[u].val <<"  " << tr[tr[u].l].val << "  " << tr[tr[u].r].val << endl;
    dfscheck(tr[u].l);
    dfscheck(tr[u].r);
   }

  // 删除多个值
  int del(int root, int v) {
    int x, y, z;
    split(root, v, x, z);
    split(x, v - 1, x, y);
    gc(y);
    root = merge(x, z);
    return root;
  }
  
  int delOne(int root, int v) {
    int x, y, z;
    // 先找到 v 的分割点 => x <= v < z
    split(root, v, x, z);
    // 再按 v-1 分裂 x 树 => x <= v-1 < y <= v
    split(x, v - 1, x, y);
    // y 就是值等于 v 的节点, 删除它
    // 如果找不到 v, y 就是空树, 其左右孩子都是 0, 不影响
    int oldy = y;
    y = merge(tr[y].l, tr[y].r);
    tr[oldy].l = tr[oldy].r = 0; 
    gc(oldy);
    // 再把 x, y, z 合并起来
    return merge(merge(x, y), z);
  }
  
} t;

const int M = 1e6 + 10;
int a[N];
int ids[M], roots[M];
int tot = 0;

void dfs(int num1, int num2, int u) { //merge num1 -> num2
  if(!u) return;
  roots[ids[num2]] = t.insert(roots[ids[num2]], t.tr[u].val);
  roots[t.tr[u].val] = t.delOne(roots[t.tr[u].val], ids[num1]);
  roots[t.tr[u].val] = t.insert(roots[t.tr[u].val], ids[num2]);
  dfs(num1, num2, t.tr[u].l);
  dfs(num1, num2, t.tr[u].r);
}

void solve() {
  memset(ids, -1, sizeof ids);
  memset(roots, 0, sizeof roots);
  
  int n, m;
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }

  int id = 0;
  for(int i = 1; i <= n; i++) {
    if(ids[a[i]] == -1) {
      ids[a[i]] = id++;
    }
  }

  for(int i = 2; i <= n; i++) {
    if(a[i] != a[i - 1]) {
      roots[ids[a[i]]] = t.insert(roots[ids[a[i]]], ids[a[i - 1]]);
      roots[ids[a[i - 1]]] = t.insert(roots[ids[a[i - 1]]], ids[a[i]]);
      tot += 2;
    }
  }
  
  for(int i = 0; i < m; i++) {
    int op;
    scanf("%d", &op);
    if(op == 1) {
      int x, y;
      scanf("%d%d", &x, &y); //x -> y
      if(x == y || ids[x] == -1) continue;
      if(ids[y] != -1) { //merge x to y
        tot -= (t.tr[roots[ids[x]]].sz + t.tr[roots[ids[y]]].sz);
        roots[ids[y]] = t.del(roots[ids[y]], ids[x]);
        roots[ids[x]] = t.del(roots[ids[x]], ids[y]);
        dfs(x, y, roots[ids[x]]);
        t.gc(roots[ids[x]]);
        tot += t.tr[roots[ids[y]]].sz;  
        roots[ids[x]] = 0;
        ids[x] = -1;  
      } else { //just change color
        ids[y] = ids[x];
        ids[x] = -1;
      }
    } else { //query
      printf("%d\n", tot / 2 + 1);
    }
  }
}

int main() {
  int t = 1;
  while(t--) {
    solve();
  }  
}

