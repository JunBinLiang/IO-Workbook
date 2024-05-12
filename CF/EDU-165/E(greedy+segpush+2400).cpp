#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector

const int MAX = 3e5 + 100;

struct Node {
  int l, r;
  int tag;
  int mn;
} tr[MAX * 4];

void build(int u) {
  int l = tr[u].l, r = tr[u].r;
  if(l == r) {
    return;
  }
  int left = u * 2 + 1, right = u * 2 + 2;
  int mid = l + (r - l) / 2;
  tr[left] = {l, mid, 0, 0};
  tr[right] = {mid + 1, r, 0, 0};
  build(left);
  build(right);
}

//add a constant value to a range
void pushdown(int u) {
  int l = tr[u].l, r = tr[u].r;
  if(l == r || tr[u].tag == 0) return;

  int left = u * 2 + 1, right = u * 2 + 2;
  tr[left].tag += tr[u].tag;
  tr[left].mn += tr[u].tag;
  tr[right].tag += tr[u].tag;
  tr[right].mn += tr[u].tag;
  tr[u].tag = 0;
}

void update(int u, int s, int e, int v) {
  int l = tr[u].l, r = tr[u].r;
  if(l == s && r == e) {
    tr[u].mn += v;
    tr[u].tag += v;
    return;
  }
  pushdown(u);
  int left = u * 2 + 1, right = u * 2 + 2;
  int mid = l + (r - l) / 2;
  if(e <= mid) {
    update(left, s, e, v);
  } else if(s >= mid + 1) {
    update(right, s, e, v);
  } else {
    update(left, s, mid, v);
    update(right, mid + 1, e, v);
  }
  tr[u].mn = min(tr[left].mn, tr[right].mn);
}

int query(int u, int s, int e) { 
   int l = tr[u].l, r = tr[u].r;
   if(l == s && r == e) {
    return tr[u].mn;
   }
   pushdown(u);
   int left = u * 2 + 1, right = u * 2 + 2;
   int mid = l + (r - l) / 2;
   if(e <= mid) {
    return query(left, s, e);
   } else if(s >= mid + 1) {
    return query(right, s, e);
   } else {
    return min(query(left, s, mid), query(right, mid + 1, e));
   }
}


const int INF = 1e9;
const int N = 3e5 + 10;
int a[N], pos[N];
pair<int, int> range[N];

struct Change {
  int l, r, v;
};

void solve() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for(int i = 0; i <= n; i++) {
      pos[i] = -1;
      range[i] = {-1, -1};
    }

    int ans = 0;
    tr[0] = {0, n -1, 0, 0};
    build(0);
    int L = 0;
    vector<Change> changes;
    for(int i = 0; i < n; i++) {
      if(pos[a[i]] == -1) {
        update(0, L, i, 1);
        changes.push_back({L, i, -1});
        range[a[i]] = {L, i};
      } else {
        update(0, range[a[i]].first, range[a[i]].second, -1);
        update(0, pos[a[i]] + 1, i, 1);
        range[a[i]] = {pos[a[i]] + 1, i};
        changes.push_back({range[a[i]].first, range[a[i]].second, 1});
        changes.push_back({pos[a[i]] + 1, i, -1});
      }

      int mn = query(0, L, i);
      if(mn == 0) {
        ans++;
        L = i + 1;
        //reset
        for(auto& c : changes) {
          update(0, c.l, c.r, c.v);
        }
        changes.clear();
      }
      pos[a[i]] = i;
    }
    printf("%d\n", ans);
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
