//https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P4146
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
const int N = 1e5 + 100;
struct FHQ {
    struct {
        int l, r;  // 左右孩子
        ll val;   // 节点权值
        ll mx;
        int rnd;   // 随机值
        int size;  // 子树大小
        int rev_tag;  // 翻转延迟标记
        int add_tag;  // 覆盖延迟标记
        int add_val;  // 覆盖更新的值
    } tr[N];
    
    int gctop = -1, stk[N];
    int root = 0, n = 0;  // 根节点, 最新节点的下标
                          //
    inline int _rand() {
        seed *= 260817;
        return int(seed);
    }

    void gc(int u) {
      if(!u) return;
      stk[++gctop] = u;
      gc(tr[u].l);
      gc(tr[u].r);
    }

    // 创建一个新节点
    int newnode(int v) {
      int id = -1;
      if(gctop >= 0) {
        id = stk[gctop--];
      } else {
        id = ++n;
      }
      tr[id].val = tr[id].mx = v;
      tr[id].rnd = _rand();
      tr[id].size = 1;
      tr[id].rev_tag = tr[id].add_tag = tr[id].add_val = 0;
      tr[id].l = tr[id].r = 0;
      return id;
    }

    void rev(int u) {
      if(!u) return;
      tr[u].rev_tag ^= 1;
      swap(tr[u].l, tr[u].r);
    }

    void add(int u, int c) {
      if(!u) return;
      tr[u].val += c;
      tr[u].mx += c;
      tr[u].add_tag = 1;
      tr[u].add_val += c;
    }

    void pushup(int p) { 
      tr[p].size = tr[tr[p].l].size + tr[tr[p].r].size + 1; 
      tr[p].mx = max(tr[p].val, max(tr[tr[p].l].mx, tr[tr[p].r].mx));
    }

    void pushdown(int p) {
      if(tr[p].rev_tag) {
        rev(tr[p].l);
        rev(tr[p].r);
        tr[p].rev_tag = 0;
      }
      if(tr[p].add_tag) {
        add(tr[p].l, tr[p].add_val);
        add(tr[p].r, tr[p].add_val);
        tr[p].add_tag = 0;
        tr[p].add_val = 0;
      }
    }

  //split by size
  void split(int u, int sz, int &x, int &y) {
    if (!u) {
      x = y = 0;
      return;
    }
    pushdown(u);
    if(tr[tr[u].l].size < sz) {
      x = u;
      split(tr[u].r, sz - tr[tr[u].l].size - 1, tr[u].r, y);
    }
    else {
      y = u;
      split(tr[u].l, sz, x, tr[u].l);
    }
    pushup(u);
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

  // 插入一个值
  void insert(int v) {
    // 按 v 分裂, 找到插入点 x <=v < y
    int x, y;
    split(root, v, x, y);
    // 新建节点
    int z = newnode(v);
    // 依次合并 x, z 和 y (权值 val 也满足如此顺序)
    root = merge(merge(x, z), y);
  }

  // 删除一个值
  void del(int v) {
    int x, y, z;
    // 先找到 v 的分割点 => x <= v < z
    split(root, v, x, z);
    // 再按 v-1 分裂 x 树 => x <= v-1 < y <= v
    split(x, v - 1, x, y);
    // y 就是值等于 v 的节点, 删除它
    // 如果找不到 v, y 就是空树, 其左右孩子都是 0, 不影响
    y = merge(tr[y].l, tr[y].r);
    // 再把 x, y, z 合并起来
    root = merge(merge(x, y), z);
  }
};


int main() {
  FHQ t;
  t.tr[0].mx = -1e18; //处理0，处理pushup时为leaf的情况 
  int n, m;
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; i++) t.root = t.merge(t.root, t.newnode(0));
  while(m--) {
    int op, l, r, v;
    scanf("%d", &op);
    if(op == 1) {
      scanf("%d%d%d", &l, &r, &v);
      int x, y, z;
      t.split(t.root, r, x, z);
      t.split(x, l - 1, x, y);
      t.add(y, v);
      t.root = t.merge(x, t.merge(y, z));
    } else if(op == 2) {
      scanf("%d%d", &l, &r);
      int x, y, z;
      t.split(t.root, r, x, z);
      t.split(x, l - 1, x, y);
      t.rev(y);
      t.root = t.merge(x, t.merge(y, z));
    } else {
      scanf("%d%d", &l, &r);
      int x, y, z;
      t.split(t.root, r, x, z);
      t.split(x, l - 1, x, y);
      printf("%lld\n", t.tr[y].mx);
      t.root = t.merge(x, t.merge(y, z));
    }
  }
  
  return 0;
}
