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

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

namespace Seg1 {
    const int MAX = 200000 + 100;
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
}

namespace Seg2 { //push seg
    const int N = 2e5 + 100;
    struct Node {
        int l, r;
        long long sum, realsum;
        int tag;
    } tr[N * 4];

    void build(int u) {
        if(tr[u].l == tr[u].r) {
            return;
        }
        int mid = tr[u].l + (tr[u].r - tr[u].l) / 2;
        tr[u * 2 + 1] = {tr[u].l, mid, 0, 0, 0};
        tr[u * 2 + 2] = {mid + 1, tr[u].r, 0, 0, 0};
        build(u * 2 + 1);
        build(u * 2 + 2);
    }

    void pushdown(int u) {
        if(tr[u].l == tr[u].r || tr[u].tag == 0) {
            return;
        }
        int left = u * 2 + 1, right = u * 2 + 2;
        tr[left].realsum += (tr[left].sum + 0ll) * tr[u].tag;
        tr[right].realsum += (tr[right].sum + 0ll) * tr[u].tag;
        tr[u * 2 + 1].tag += tr[u].tag;
        tr[u * 2 + 2].tag += tr[u].tag;
        tr[u].tag = 0;
    }

    void pushup(int u) {
        if(tr[u].l == tr[u].r) {
            return;
        }
        int left = u * 2 + 1, right = u * 2 + 2;
        tr[u].sum = tr[left].sum + tr[right].sum;
        tr[u].realsum = tr[left].realsum + tr[right].realsum;
    }

    //Update a range
    void updatereange(int u, int s, int e, int add) {
        if(tr[u].l == s && tr[u].r == e) {
            tr[u].tag += add;
            tr[u].realsum += (tr[u].sum * add);
            return;
        }
        pushdown(u);
        int mid = tr[u].l + (tr[u].r - tr[u].l) / 2;
        int left = u * 2 + 1, right = u * 2 + 2;
        if(e <= mid) {
            updatereange(left, s, e, add);
        } else if(s >= mid + 1) {
            updatereange(right, s, e, add);
        } else {
            updatereange(left, s, mid, add);
            updatereange(right, mid + 1, e, add);
        }
        pushup(u);
    }

    void update(int u, int index, long long val) { //single point update
        int l = tr[u].l, r = tr[u].r;
        if(l == r) {
            tr[u].sum = val;
            tr[u].realsum = 0;
            return;
        }
        pushdown(u);
        int mid = l + (r - l) / 2;
        int left = u * 2 + 1, right = u * 2 + 2;
        if(index <= mid) {
            update(left, index, val);
        } else {
            update(right, index, val);
        }
        pushup(u);
    }

    long long query(int u, int s, int e) {
        if(tr[u].l == s && tr[u].r == e) {
            return tr[u].realsum;
        }
        pushdown(u);
        int mid = tr[u].l + (tr[u].r - tr[u].l) / 2;
        int left = u * 2 + 1, right = u * 2 + 2;
        if(e <= mid) {
            return query(left, s, e);
        } else if(s >= mid + 1) {
            return query(right, s, e);
        } else {
            return query(left, s, mid) + query(right, mid + 1, e);
        }
    }
}

const int SIZE = 200000 + 100;
struct Fenwick {
  long long tree[SIZE];
  void init(int n) {
    for(int i = 0; i <= n + 1; i++) tree[i] = 0;
  }

  void update(int i, long long val) {
    i++;
    while(i < SIZE){
      tree[i] += val;
      i += (i & -i);
    }
  }

  long long pre(int i) {
    long long sum = 0;
    while(i>0){
      sum += tree[i];
      i -= ( i & -i);
    }
    return sum;
  }
  long long query(int i, int j) {
      return pre(j + 1) - pre(i);
  }
} tr1;

struct Q {
    int l, r, i;
    bool operator<(const Q& other) {
        return r < other.r;
    }
};

struct Interval {
    int l, r, i;
    bool operator<(const Interval& other) {
        return r < other.r;
    }
};

const int N = 2e5 + 100;
long long ans[N];
vector<pair<int, int>> q1[N], q2[N];

void solve() {
    int n, k, m;
    scanf("%d%d%d", &n, &k, &m);
    vector<int> a(n + 1);
    for(int i = 0; i <= n; i++) {
        q1[i].clear();
        q2[i].clear();
    }
    for(int i = 0; i <= m; i++) ans[i] = 0;

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
    vector<int> right(b.size(), b.size()), left(b.size(), 0);
    for(int i = 0; i < b.size(); i++) {
        while(stk.size() > 0 && b[i] < b[stk.back()]) {
            int index = stk.back(); stk.pop_back();
            right[index] = i;
        }
        stk.push_back(i);
    }
    stk.clear();
    for(int i = b.size() - 1; i >= 0; i--) {
        while(stk.size() > 0 && b[i] <= b[stk.back()]) {
            int index = stk.back(); stk.pop_back();
            left[index] = i;
        }
        stk.push_back(i);
    }
    
    Seg1 :: tree[0] = {0, b.size(), 500000, -1};
    Seg1 :: build(0);
    for(int i = 0; i < b.size(); i++) {
        Seg1 :: update(0, i, b[i]);
    }

    //case 1
    vector<Interval> in;
    for(int i = 1; i < b.size(); i++) {
        int l = left[i], r = right[i];
        in.push_back({l, r, i});
    }
    vector<Q> query;
    for(int i = 0; i < m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        r = r - k + 1; // real r
        query.push_back({l, r, i});
        q1[l].push_back({r, i});
        q2[r].push_back({l, i});
    }
    sort(query.begin(), query.end());
    sort(in.begin(), in.end());
    int j = 0;
    tr1.init(b.size() + 1);
    for(int i = 0; i < query.size(); i++) {
        while(j < in.size() && in[j].r <= query[i].r) {
            int l = in[j].l, r = in[j].r, mid = in[j].i;
            long long w = (mid - l + 0ll) * (r - mid + 0ll) * b[in[j].i];
            tr1.update(l, w);
            j++;
        }
        ans[query[i].i] += tr1.query(query[i].l, query[i].r);
    }
  
    //case2
    for(int i = 0; i < query.size(); i++) {
        int l = query[i].l, r = query[i].r, index = query[i].i;
        pair<int, int> p = Seg1 :: query(0, l, r);
        ans[index] = ans[index] + ((p.second - l + 1ll) * (r - p.second + 1ll) * p.first);
    }
    
    //case 3, 4
    stk.clear();
    Seg2 :: tr[0] = {0, b.size(), 0, 0, 0};
    Seg2 :: build(0);
    for(int i = 1; i < b.size(); i++) {
        while(stk.size() > 0 && b[i] < b[stk.back()]) {
            int index = stk.back(); stk.pop_back();
            Seg2 :: update(0, index, 0);
        }
        Seg2 :: update(0, left[i], (i - left[i] + 0ll) * b[i]);
        Seg2 :: updatereange(0, 0, b.size() - 1, 1);
        stk.push_back(i);
        for(pair<int, int>& p : q2[i]) {
            int l = p.first, index = p.second;
            ans[index] += Seg2 :: query(0, l, i);
        }
    }
    
    //case4
    stk.clear();
    Seg2 :: tr[0] = {0, b.size(), 0, 0, 0};
    Seg2 :: build(0);
    for(int i = b.size() - 1; i >= 1; i--) {
        while(stk.size() > 0 && b[i] <= b[stk.back()]) {
            int index = stk.back(); stk.pop_back();
            Seg2 :: update(0, index, 0);
        }
        Seg2 :: update(0, right[i], (right[i] - i + 0ll) * b[i]);
        Seg2 :: updatereange(0, 0, b.size() - 1, 1); 
        stk.push_back(i);
        for(pair<int, int>& p : q1[i]) {
            int r = p.first, index = p.second;
            ans[index] += Seg2 :: query(0, i, r);
        }
    }
    
    for(int i = 0; i < m; i++) {
        printf("%lld\n", ans[i]);
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
