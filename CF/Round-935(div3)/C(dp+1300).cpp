#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector

void solve() {
  int n, m;
  cin >> n >> m;
  vector<int> a(n + 1), b(n + 1);
  for(int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for(int i = 1; i <= n; i++) {
    cin >> b[i];
  }

  ll s = 0;
  vector<ll> ans(n + 1);
  for(int i = n; i >= 1; i--) {
    int v = min(a[i], b[i]);
    ans[i] = s + a[i];
    s += v; 
  }

  ll v = ans[1];
  for(int i = 1; i <= m; i++) {
    v = min(v, ans[i]);
  }
  cout << v << endl;
}


int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}

