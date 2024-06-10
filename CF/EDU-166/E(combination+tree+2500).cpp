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
using ull = unsigned long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)

const int MOD = 998244353;
const int N = 3e5 + 10;
int pre[N];
int id = 1;

struct Node {
    int l, r, v;
} tr[N * 16];

void dfs(vector<int>& order, int u) {
    if(u == -1) return;
    int v = tr[u].v;
    if(pre[v] == u) { //leaf
        order.push_back(v);
        return;
    }
    dfs(order, tr[u].l);
    dfs(order, tr[u].r);
}

void solve() {
    int n, m;
    scanf("%d%d", &n, &m);
    memset(pre, -1, sizeof pre);
    vector<int> L(m), R(m);
    for(int i = 0; i < m; i++) scanf("%d", &L[i]);
    for(int i = 0; i < m; i++) scanf("%d", &R[i]);

    tr[id] = {-1, -1, L[0]};
    pre[L[0]] = id;
    id++;
    tr[id] = {-1, -1, R[0]};
    pre[R[0]] = id;
    id++;
    tr[0].l = 1;
    tr[0].r = 2;

    for(int i = 1; i < m; i++) {
        if(L[i] > R[i]) {
            int u = pre[L[i]];
            tr[id] = {-1, -1, L[i]};
            pre[L[i]] = id;
            id++;
            tr[id] = {-1, -1, R[i]};
            pre[R[i]] = id;
            id++;
            tr[u].l = id - 2;
            tr[u].r = id - 1;
        } else {
            int u = pre[R[i]];
            tr[id] = {-1, -1, R[i]};
            pre[R[i]] = id;
            id++;
            tr[id] = {-1, -1, L[i]};
            pre[L[i]] = id;
            id++;
            tr[u].l = id - 1;
            tr[u].r = id - 2;
        }
    }

    vector<int> order;
    dfs(order, 0);
    
    vector<int> count(n + 1);
    for(int i = 0; i < order.size(); i++) {
        if(i == 0 || i == order.size() - 1) {
            count[order[i]]++;
        }
        if(i > 0) {
            count[max(order[i], order[i - 1])]++;
        }
    }
    
    ll ans = 1;
    for(int i = n - 1; i >= 1; i--) { //n is always exist
        if(pre[i] == -1) {
            ans = (ans * count[i + 1]) % MOD;
            count[i] = 1;
        }
        count[i] += count[i + 1];
    }
    
    cout << ans << endl;
} 



int main(){
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
