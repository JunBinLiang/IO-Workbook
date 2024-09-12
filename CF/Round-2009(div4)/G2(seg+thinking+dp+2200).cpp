#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_set>
#include<set>
#include<unordered_map>
#include<map>
#include<string>
#include <string.h>
#include <bitset>
#include <queue>
#include <cmath>

using namespace std;

const int MAX = 200000 + 100;

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

struct Node {
  int l, r;
  int mn, mnIndex;
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, 500000, -1};
  tree[id * 2 + 2] = {mid + 1, r, 500000, -1};
  build(id * 2 + 1);
  build(id * 2 + 2);
}

void update(int id, int index, int val) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    tree[id].mnIndex = l;
    tree[id].mn = min(tree[id].mn, val);  
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(index <= mid) {
    update(left, index, val);
  } else {
    update(right, index, val);
  }
  tree[id].mn = min(tree[left].mn, tree[right].mn);
  if(tree[left].mn <= tree[right].mn) {
    tree[id].mnIndex = tree[left].mnIndex;
  } else {
    tree[id].mnIndex = tree[right].mnIndex;
  }
}

pair<int, int> query(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return {tree[id].mn, tree[id].mnIndex};
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query(left, s, e);
  } else if(s >= mid + 1) {
      return query(right, s, e);
  } else {
    pair<int, int> p1 = query(left, s, mid), p2 = query(right, mid + 1, e);
    if(p1.first <= p2.first) return p1;
    else return p2;
  }
}

void solve() {
    int n, k, m;
    scanf("%d%d%d", &n, &k, &m);
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        a[i] -= i;
    }

    vector<int> b(1);
    map<int, int> f, g;
    for(int i = 1; i <= n; i++) {
        f[a[i]]++;
        g[f[a[i]]]++;
        if(f[a[i]] > 1) {
            g[f[a[i]] - 1]--;
            if(g[f[a[i]] - 1] == 0) g.erase(f[a[i]] - 1);
        } 

        if(i >= k) {
            auto it = g.end();
            it--;
            b.push_back(k - (it -> first));
            int v = a[i - k + 1];
            f[v]--;
            if(f[v] > 0) g[f[v]]++;
            g[f[v] + 1]--;
            if(g[f[v] + 1] == 0) g.erase(f[v] + 1);
        }
    }

    vector<int> stk;
    vector<int> nxt(b.size(), -1);
    vector<long long> dp(b.size());
    for(int i = 1; i < b.size(); i++) {
        while(stk.size() > 0 && b[i] < b[stk.back()]) {
            int index = stk.back(); stk.pop_back();
            nxt[index] = i;
        }
        stk.push_back(i);
    }

    for(int i = b.size() - 1; i >= 0; i--) { //cost to reach end
        if(nxt[i] == -1) { //minimum
            dp[i] = (b.size() - i + 0ll) * b[i];
        } else {
            dp[i] = dp[nxt[i]] + (nxt[i] - i + 0ll) * b[i];
        }
    }
    
    tree[0] = {0, b.size() + 1, 500000, -1};
    build(0);
    for(int i = 0; i < b.size(); i++) {
        update(0, i, b[i]);
    }
    
    for(int i = 0; i < m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        r = r - k + 1; // real r
        pair<int, int> p = query(0, l, r);
        long long ans = dp[l]; //cost to end
        int index = p.second;
        ans -= dp[index];
        ans += ((r - index + 1ll) * b[index]);
        printf("%lld\n", ans);
    }
}     

int main() {
    int t = 1;
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
