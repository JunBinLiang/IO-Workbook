//https://qoj.ac/submission/330042  
//洛谷卡时间。。。

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

const int N = 100000 + 10;
int ans[N], L[2010], R[2010];
bool vis1[N], vis2[N];
vector<int> T[2010];

struct E {
  int u, v, w, t, i;
} e[N * 2];

int ee[N * 2];

int cur[N * 2];
int curIdx = 0;

struct Q {
  int u, w, t, i;
  bool operator< (const Q& other) {
    return w > other.w;
  }
} q[N];

bool comp1(E& e1, E& e2) {
  return e1.t < e2.t;
}

bool comp2(E& e1, E& e2) {
  return e1.w > e2.w;
}

//DSU
struct Node {
    int fax, fay, w, sz;
} stk[N];

int p[N], rk[N], sz[N]; 
int top = 0;
int find(int x) {
  return p[x] == x ? x : find(p[x]);
}

bool merge(int u, int v) {
  int fax = find(u), fay = find(v);
  if(rk[fax] > rk[fay]) {
    swap(fax, fay);
  }
  
  //注意这里，否则树的高度会不一样而导致TLE
  if(fax != fay) {
    stk[top++] = (Node){fax, fay, (rk[fax] == rk[fay]), sz[fay]};
    p[fax] = fay;
    sz[fay] += sz[fax];
    if(rk[fay] == rk[fax]) rk[fay]++;
    return true;
  }
  return false;
}

void undo() {
  while(top > 0) {
    top--;
    int fax = stk[top].fax, fay = stk[top].fay;
    p[fax] = fax;
    rk[fay] -= stk[top].w;
    sz[fay] = stk[top].sz;
  }
}
////////////////////////////////////////////////////////////////////

void init(int n) {
  top = 0;
  for(int i = 0; i <= n; i++) {
    p[i] = i, sz[i] = 1, rk[i] = 0;
  }
}

int cnt = 0;
void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  for(int i = 0; i < m; i++) {
    scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
    e[i].t = 0;
    e[i].i = i;
    ee[i] = e[i].w;
  }
  
  int k = 0, ti = 0, o = 0;
  scanf("%d", &o);
  for(int i = 0; i < o; i++) {
    int op;
    scanf("%d", &op);
    if(op == 1) {
      int ith, w;
      scanf("%d%d", &ith, &w);
      e[m] = {e[ith - 1].u, e[ith - 1].v, w, ++ti, ith - 1};
      m++;
    } else {
      scanf("%d%d", &q[k].u, &q[k].w);
      q[k].t = ++ti;
      q[k].i = k;
      k++;
    }
  }

  sort(e, e + m, comp1); //按w 从大到小排序
  sort(q, q + k); //按t 从小到大排序

  //分块范围初始化
  int s = sqrt(m * 2);
  int t = 0;
  int start = 0;
  for(int i = 0; i < m; i += s) {
    L[t] = i;
    R[t] = min(m - 1, i + s - 1);
    if(e[R[t]].t == 0) start = t;
    t++;
  }
  //分块分配处理
  for(int i = 0; i < k; i++) {
    int j = start;
    while(j < t && e[R[j]].t <= q[i].t) j++;
    T[min(j, t - 1)].push_back(i);
  }
  
  for(int i = 0; i < t; i++) {
    int l = L[i], r = R[i];
    if(T[i].size() == 0) continue;
    init(n);
    sort(e, e + l, comp2);
    for(int o = l; o <= r; o++) {
      vis1[e[o].i] = true;
    }

    curIdx = 0;
    int j = 0;
    for(int& x : T[i]) {
      int u = q[x].u, w = q[x].w, idx = q[x].i;
      while(j < l && e[j].w >= w) {
        if(e[j].w != ee[e[j].i]) { //not the newest
        } else {
          if(vis1[e[j].i]) {
            cur[curIdx++] = j;
          } else {
            merge(e[j].u, e[j].v);
          }
        }
        j++;
      }
      
      top = 0;
      for(int o = r; o >= l; o--) {
        if(e[o].t <= q[x].t) {
          if(!vis2[e[o].i]) {
            if(e[o].w >= w) {
              merge(e[o].u, e[o].v);
            }
            vis2[e[o].i] = true;
          }
        }
      }

      for(int o = curIdx - 1; o >= 0; o--) {
        if(e[cur[o]].t <= q[x].t) {
          if(!vis2[e[cur[o]].i]) {
            if(e[cur[o]].w >= w) {
              merge(e[cur[o]].u, e[cur[o]].v);
            }
            vis2[e[cur[o]].i] = true;
          }
        }
      }
      for(int o = l; o <= r; o++) vis2[e[o].i] = false;
      ans[idx] = sz[find(u)];
      undo();
    }

    for(int o = l; o <= r; o++) { //update edge with the newest info
      ee[e[o].i] = e[o].w;
      vis1[e[o].i] = false;
    }
  }
  
  for(int i = 0; i < k; i++) {
    printf("%d\n", ans[i] == 0 ? 1 : ans[i]);
  }
}

int main() {
  int t = 1;
  while(t--) {
    solve();
  }
  return 0;
}
