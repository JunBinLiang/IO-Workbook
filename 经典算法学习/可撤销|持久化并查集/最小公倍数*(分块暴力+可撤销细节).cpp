//https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P3247
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
bool ans[N];
int L[1010], R[1010];
vector<int> T[1010];

struct E {
  int u, v, a, b;
} e[N];

struct Q {
  int u, v, a, b, i;
  bool operator< (const Q& other) {
    return b < other.b;
  }
} q[N];

bool comp1(E& e1, E& e2) {
  return e1.a < e2.a;
}

bool comp2(E& e1, E& e2) {
  return e1.b < e2.b;
}

//DSU
struct Node {
    int fax, fay, w, a, b;
} stk[N];

int p[N], rk[N], maxa[N], maxb[N]; 
int top = 0;
int find(int x) {
    if (p[x] != x) return find(p[x]);
    return p[x];
}

bool merge(int u, int v, int a, int b) {
  int fax = find(u), fay = find(v);
  if(rk[fax] > rk[fay]) {
    swap(fax, fay);
  }
  
  //注意这里，否则树的高度会不一样而导致TLE
  stk[top++] = (Node){fax, fay, (rk[fax] == rk[fay]) && (fax != fay), maxa[fay], maxb[fay]};
  maxa[fay] = max(maxa[fay], a);
  maxb[fay] = max(maxb[fay], b);
  
  if(fax != fay) {
    p[fax] = fay;
    maxa[fay] = max(maxa[fay], maxa[fax]);
    maxb[fay] = max(maxb[fay], maxb[fax]);
    if(rk[fay] == rk[fax]) rk[fay]++;
    return true;
  }
  return false;
}

void undo() {
  while(top > 0) {
    top--;
    int fax = stk[top].fax, fay = stk[top].fay, a = stk[top].a, b = stk[top].b;
    p[fax] = fax;
    rk[fay] -= stk[top].w;
    maxa[fay] = a;
    maxb[fay] = b;
  }
}
////////////////////////////////////////////////////////////////////

void init(int n) {
  top = 0;
  for(int i = 0; i <= n; i++) p[i] = i, maxa[i] = maxb[i] = -1, rk[i] = 0;
}

int cnt = 0;
void solve() {
  int n, m;
  scanf("%d%d", &n, &m);

  for(int i = 0; i < m; i++) {
    scanf("%d%d%d%d", &e[i].u, &e[i].v, &e[i].a, &e[i].b);
  }
  sort(e, e + m, comp1);

  int k;
  cin >> k;
  for(int i = 0; i < k; i++) {
    scanf("%d%d%d%d", &q[i].u, &q[i].v, &q[i].a, &q[i].b);
    q[i].i = i;
    if(q[i].a == 0) cnt++;
  }
  sort(q, q + k);
  
  //分块范围初始化
  int s = sqrt(m);
  int t = 0;
  for(int i = 0; i < m; i += s) {
    L[t] = i;
    R[t] = min(m - 1, i + s - 1);
    t++;
  }

  

  for(int i = 0; i < k; i++) {
    int j = 0;
    while(j < t && e[R[j]].a <= q[i].a) j++;
    T[min(j, t - 1)].push_back(i);
  }
  
  //for(int i = 0; i < T.size(); i++) {
      //cout << i << "  " << blocks[i].first << "  " << blocks[i].second << T[i] << endl;
  //}
  
  for(int i = 0; i < t; i++) {
    int l = L[i], r = R[i];
    init(n);
    sort(e, e + l, comp2);
    int j = 0;
    
    for(int& x : T[i]) {
      int u = q[x].u, v = q[x].v, a = q[x].a, b = q[x].b, idx = q[x].i;
      while(j < l && e[j].b <= b) {
        merge(e[j].u, e[j].v, e[j].a, e[j].b);
        j++;
      }
      
      //处理当前分块
      top = 0;
      for(int o = l; o <= r; o++) {
        if(e[o].a <= a && e[o].b <= b) {
          merge(e[o].u, e[o].v, e[o].a, e[o].b);
        }
      }
      
      int fau = find(u), fav = find(v);
      if(fau == fav && maxa[fau] == a && maxb[fau] == b) {
        ans[idx] = true;
      }
      undo();
    }
  }
  
  for(int i = 0; i < k; i++) {
    if(ans[i]) printf("Yes\n");
    else printf("No\n");
  }
}

int main() {
  int t = 1;
  while(t--) {
    solve();
  }
  return 0;
}
