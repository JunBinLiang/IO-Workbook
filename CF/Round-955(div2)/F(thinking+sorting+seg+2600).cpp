#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string.h>
#include <random>
#include <chrono>

using namespace std;
using ll = long long;

template <typename T>
ostream &operator<<(ostream &out, const set<T> &a)
{
  out << "["; bool first = true;
  for (auto v : a)
  {
    out << (first ? "" : ", ");
    out << v;
    first = 0;
  } out << "]";
  return out;
}

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

const int MAX = 1e6 + 100;
const int INF = 1e9;
struct Node {
  int l, r;
  int mn, mx;
} tr[MAX * 4];

void build(int id) {
  int l = tr[id].l, r = tr[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tr[id * 2 + 1] = {l, mid, INF, -INF};
  tr[id * 2 + 2] = {mid + 1, r, INF, -INF};
  build(id * 2 + 1);
  build(id * 2 + 2);
}

void update(int id, int index, int val) { 
  int l = tr[id].l, r = tr[id].r;
  if(l == r) {
    tr[id].mn = tr[id].mx = val;
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(index <= mid) {
    update(left, index, val);
  } else {
    update(right, index, val);
  }
  tr[id].mn = min(tr[left].mn, tr[right].mn);
  tr[id].mx = max(tr[left].mx, tr[right].mx);
}

int query1(int id, int s, int e) {
  int l = tr[id].l, r = tr[id].r;
  if(l == s && r == e){
    return tr[id].mn;
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
  int l = tr[id].l, r = tr[id].r;
  if(l == s && r == e){
    return tr[id].mx;
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


const int N = 1e6 + 50;
void solve() {
  int n, m;
  scanf("%d", &n);
  vector<int> a(n + 1);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }

  scanf("%d", &m);
  vector<pair<int, int>> q(m);
  for(int i = 0; i < m; i++) {
    scanf("%d%d", &q[i].first, &q[i].second);
  }

  vector<int> b;
  for(int i = 1; i <= n; i++) b.push_back(a[i]);
  for(int i = 0; i < m; i++) b.push_back(q[i].second);
  sort(b.begin(), b.end());
  int rk = 1;
  unordered_map<int, int> mp;
  for(int i = 0; i < b.size(); i++) {
    if(mp.find(b[i]) == mp.end()) {
      mp[b[i]] = rk++;
    }
  }
  for(int i = 1; i <= n; i++) a[i] = mp[a[i]];
  
  set<int> ls, rs;
  for(int i = 1; i < n; i++) {
    if(a[i] > a[i + 1]) {
      ls.insert(i);
      rs.insert(i + 1);
    }
  }
  
  tr[0] = {0, n, INF, -INF};
  build(0);
  for(int i = 1; i <= n; i++) {
    update(0, i, a[i]);
  }

  for(int i = -1; i < (int)(q.size()); i++) {
    if(i != -1) {
      int pos = q[i].first, val = mp[q[i].second];
      if(pos + 1 <= n && a[pos] > a[pos + 1]) {
        ls.erase(pos);
        rs.erase(pos + 1);
      }
      if(pos - 1 >= 1 && a[pos - 1] > a[pos]) {
        ls.erase(pos - 1);
        rs.erase(pos);
      }

      a[pos] = val;
      update(0, pos, val);
      if(pos + 1 <= n && a[pos] > a[pos + 1]) {
        ls.insert(pos);
        rs.insert(pos + 1);
      }
      if(pos - 1 >= 1 && a[pos - 1] > a[pos]) {
        ls.insert(pos - 1);
        rs.insert(pos);
      }
    }

    if(ls.size() == 0) {
      printf("-1 -1\n");
    } else {
      int L = -1, R = -1;
      auto it1 = ls.begin();
      int rmn = query1(0, *it1 + 1, n);
      int l = 1, r = *it1;
      while(l <= r) {
        int mid = l + (r - l) / 2;
        if(a[mid] > rmn) {
          L = mid;
          r = mid - 1;
        } else {
          l = mid + 1;
        }
      }

      it1 = rs.end();
      it1--;

      int lmax = query2(0, 1, *it1 - 1);
      l = *it1; r = n;
      while(l <= r) {
        int mid = l + (r - l) / 2;
        if(a[mid] < lmax) {
          R = mid;
          l = mid + 1;
        } else {
          r = mid - 1;
        }
      }
      printf("%d %d\n", L, R);
    }
  } 
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}


