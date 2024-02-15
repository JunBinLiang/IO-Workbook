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

struct E {
  int u, v, w, i;
  bool operator< (const E& other) {
    return w < other.w;
  }
};

struct Query {
  int u, v, i;
  bool operator< (const Query& other) {
    return i < other.i;
  }
};

const int N = 5e5 + 10;
bool ans[N];
int cnt[N];

vector<Query> qe[N]; //query edges


struct Node {
    int fax, fay, w;
};
vector<Node> stk;
int p[N * 2], rk[N * 2];
 
int find(int x) {
    if (p[x] != x) return find(p[x]);
    return p[x];
}

int ffind(int u) {
  return p[u] == u ? u : p[u] = ffind(p[u]);
}
 
bool merge(int u, int v) {
    int fax = find(u), fay = find(v);
    if(rk[fax] > rk[fay]) {
        swap(fax, fay);
    }
    if(fax != fay) {
        p[fax] = fay;
        stk.push_back({fax, fay, rk[fax] == rk[fay]});
        if(rk[fay] == rk[fax]) rk[fay]++;
        return true;
    }
    return false;
}
 
void undo() {
    while(stk.size()) {
        auto pa = stk.back(); stk.pop_back();
        int fax = pa.fax, fay = pa.fay, w = pa.w;
        p[fax] = fax;
        rk[fay] -= w;
    }
}

void init() {
  memset(ans, true, sizeof ans);
  memset(rk, 0, sizeof rk);
  for(int i = 0; i < N; i++) p[i] = i;
}


void solve() {
  init();
  memset(cnt, 0, sizeof cnt);
  int n, m, q;
  scanf("%d%d", &n, &m);
  
  vector<E> edges;
  for(int i = 1; i <= m; i++) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    edges.push_back({u, v, w, i});
  }
  


  scanf("%d", &q);
  for(int i = 0; i < q; i++) {
    int k;
    scanf("%d", &k);
    for(int j = 0; j < k; j++) {
      int idx;
      scanf("%d", &idx);
      idx--;
      int u = edges[idx].u, v = edges[idx].v, w = edges[idx].w;
      qe[w].push_back({u, v, i});
    }
  }

  for(int i = 0; i < N; i++) sort(qe[i].begin(), qe[i].end());

  //do MST
  sort(edges.begin(), edges.end());
  for(int i = 0; i < edges.size(); i++) {
    int u = edges[i].u, v = edges[i].v, w = edges[i].w;
    int r1 = ffind(u), r2 = ffind(v);
    if(r1 != r2) {
      p[r1] = r2;
      cnt[w]++;
    }
  }

  init();
  for(int i = 0; i < m; i++) {
    int w = edges[i].w;
    vector<Query>& a = qe[w];
    for(int x = 0; x < a.size(); x++) {
      int y = x;
      while(y < a.size() && a[x].i == a[y].i) {
        int u = a[y].u, v = a[y].v;
        if(!merge(u, v)) {
          ans[a[y].i] = false;
        }
        y++;
      }
      
      undo();
      x = y - 1;
    }

    int j = i;
    while(j < edges.size() && edges[j].w == edges[i].w) {
      int u = edges[j].u, v = edges[j].v;
      merge(u, v);
      j++;
    }
    stk.clear();
    i = j - 1;
  }


  for(int i = 0; i < q; i++) {
    if(ans[i]) printf("YES\n");
    else printf("NO\n");
  }
}


int main() {
  int t = 1;
  while(t--) {
    solve();
  }
  return 0;
}
