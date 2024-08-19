#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<unordered_set>
#include<map>
#include<string>
#include <string.h>
#include <bitset>
#include <queue>

using namespace std;

//5:38 - 6:12

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

const int MAX = 2000005 + 100;

struct Node {
  int l, r;
  int mx;
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, 0};
  tree[id * 2 + 2] = {mid + 1, r, 0};
  build(id * 2 + 1);
  build(id * 2 + 2);
}

void update(int id, int index, int val) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    tree[id].mx = val;
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(index <= mid) {
    update(left, index, val);
  } else {
    update(right, index, val);
  }
  tree[id].mx = max(tree[left].mx, tree[right].mx);
}

int query(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].mx;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query(left, s, e);
  } else if(s >= mid + 1) {
      return query(right, s, e);
  } else {
    return max(query(left, s, mid), query(right, mid + 1, e));
  }
}

map<int, int> f;
void add(int mid) {
    auto it = f.upper_bound(mid); 
    it--;
    int l = it -> first, r = it -> second;
    f.erase(l);
    update(0, l, 0);

    if(l <= mid - 1) {
        f[l] = mid - 1;
        update(0, l, mid - 1 - l + 1);
    }
    if(mid + 1 <= r) {
        f[mid + 1] = r;
        update(0, mid + 1, r - (mid + 1) + 1);
    }
    
}

void del(int mid) {
    auto it = f.upper_bound(mid); 
    int l = mid, r = mid;
    if(it != f.end() && l + 1 == it -> first) {
        int L = it -> first, R = it -> second;
        update(0, L, 0);
        r = R;
        f.erase(L);
    }

    it = f.upper_bound(mid); 
    if(it != f.begin()) {
        it--;
        if(it -> second + 1 == l) {
            int L = it -> first; int R = it -> second;
            l = L;
            f.erase(L);
            update(0, L, 0);
        }
    }
    f[l] = r;
    update(0, l, r - l + 1);
}

int dfs(int u, int k) {
    if(tree[u].l == tree[u].r) {
        return tree[u].l;
    }
    int left = u * 2 + 1, right = u * 2 + 2;
    if(tree[left].mx >= k) {
        return dfs(left, k);
    } else {
        return dfs(right, k);
    }
}


void solve() {
    int n, m;
    cin >> n;
    f.clear();
    f[1] = 4000005;
    update(0, 1, 4000005);

    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        add(x);
    }
    
    cin >> m;
    for(int i = 0; i < m; i++) {
        char op; 
        int x;
        cin >> op >> x;
        if(op == '+') {
            add(x);
        } else if(op == '-') {
            del(x);
        } else {
            int k = x;
            int ans = dfs(0, k);
            printf("%d ", ans);
        }
    }
    printf("\n");
    //clean the tree
    for(auto it = f.begin(); it != f.end(); it++) {
        int l = it -> first, r = it -> second;
        update(0, l, 0);
    }
}    

int main() {
    tree[0] = {0, 2000005};
    build(0);
    int t = 1;
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
