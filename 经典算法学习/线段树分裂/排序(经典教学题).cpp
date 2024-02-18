//https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P2824
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 4e5 + 10;
int n, m;

struct Segment_Tree{
    int son[N * 20][2], rt[N], cnt, rtc = 1;
    ll val[N * 20];
    int pool[N * 20], delcnt;
    #define ls (son[rt][0])
    #define rs (son[rt][1])
    inline int newnode(){
      return delcnt ? pool[delcnt--] : ++cnt;
    }

    inline void del(int rt){
      pool[++delcnt] = rt;
      ls = rs = val[rt] = 0;
    }

    inline void modify(int &rt, int l, int r, int p){
      if(!rt){
        rt = newnode(); //动态开点
      }
      val[rt] = 1;
      if(l == r) return ;
      int mid = l + (r - l) / 2;
      if(p <= mid) modify(ls, l, mid, p);
      else modify(rs, mid + 1, r, p);
    }

    inline int merge(int a, int b){
      if(!a || !b) return a + b;
      val[a] += val[b];
      son[a][0] = merge(son[a][0], son[b][0]);
      son[a][1] = merge(son[a][1], son[b][1]);
      del(b);
      return a;
    }

    inline void split(int &x, int y, int v, int p){
      if(val[y] == v) return;
      x = newnode();
      val[x] = val[y] - v;
      val[y] = v;
      ll q = val[son[x][0]];
      if(v <= val[son[y][p]]){
        split(son[x][p], son[y][p], v, p); 
        son[x][!p] = son[y][!p], son[y][!p] = 0;
      }else{
        split(son[x][!p], son[y][!p], v - val[son[y][p]], p);
      }
    }

    inline int query(int rt, int l, int r){
      if(l == r) return l;
      int mid = l + (r - l) / 2;
      return ls ? query(ls, l, mid) : query(rs, mid + 1, r);
    }
} t;

#define sit set<node>::iterator
struct node{
    int l,r;
    mutable int v;
    node(int L, int R = -1,int V = 0) : l(L),r(R),v(V){}
    friend bool operator<(const node& a, const node &b){
      return a.l < b.l;
    }
};
set<node>a;
inline sit split(int p){
  sit it = a.lower_bound(node(p));
  if(it != a.end() && it -> l ==p)
    return it;
  it--;
  int l = it -> l, r = it -> r, v = it -> v;
  a.erase(it);
  t.split(t.rt[p], t.rt[l], p - l, v); //线段树分裂
  a.insert(node(l, p - 1, v));
  return a.insert(node(p, r, v)).first;
}

int main(){
  scanf("%d%d", &n, &m);
  a.insert(node(n + 1, n + 1, 0));
  for(int i = 1; i <= n; i++){
    int v;
    scanf("%d", &v);
    t.modify(t.rt[i], 0, n, v);
    a.insert(node(i, i, 0));
  }
  
  while(m--){
    int opt, l, r;
    scanf("%d%d%d", &opt, &l, &r);
    sit R = split(r + 1), L = split(l);
    L -> v = opt;
    for(sit i = ++L; i != R; i++) t.merge(t.rt[l], t.rt[i -> l]);
    a.erase(L, R);
  }

  int q;
  scanf("%d", &q);
  split(q + 1), split(q);
  printf("%d\n", t.query(t.rt[q], 0, n));
}

