#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector

const int SIZE = 1e6 + 100;
struct Fenwick {
  ll tree[SIZE];
  void init(int n) {
    for(int i = 0; i <= n + 1; i++) tree[i] = 0;
  }

  void update(int i, ll val) {
    i++;
    while(i < SIZE){
      tree[i] += val;
      i += (i & -i);
    }
  }

  ll pre(int i) {
    ll sum = 0;
    while(i>0){
      sum += tree[i];
      i -= ( i & -i);
    }
    return sum;
  }
  ll query(int i, int j) {
      return pre(j + 1) - pre(i);
  }
} tr;

const int N = 1e6 + 10;
vector<pair<int, int>> q[N];
void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<int> a(n + 1), pos(n + 1); 
  vector<ll> ans(m), f(n + 1);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    pos[a[i]] = i;
  }

  tr.init(n + 1);

  for(int i = 0; i <= n; i++) q[i].clear();
  for(int i = 0; i < m; i++) {
    int l, r;
    scanf("%d%d", &l, &r);
    q[l].push_back({r, i});
  }

  for(int i = n; i >= 1; i--) {
    for(int j = a[i]; j <= n; j += a[i]) f[j] = 0;
    f[a[i]] = 1;
    for(int j = a[i]; j <= n; j += a[i]) {
      for(int k = j + j; k <= n; k += j) {
        if(pos[k] > pos[j]) {
          f[k] += f[j];
        }    
      }
    }
    
    for(int j = a[i]; j <= n; j += a[i]) {
        if(pos[j] >= i) tr.update(pos[j], f[j]);
    }

    for(auto& pa : q[i]) {
      int r = pa.first, index = pa.second;
      ans[index] = tr.query(i, r);
    }
  }


  for(int i = 0; i < m; i++) {
    printf("%lld ", ans[i]);
  }
  printf("\n");

}


int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}

