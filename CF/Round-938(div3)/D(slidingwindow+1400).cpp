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

const int N = 510;
int a[N][N];


void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<int> a(n);
  map<int, int> f, g;
  for(int i = 0; i < n; i++) cin >> a[i];
  for(int i = 0; i < m; i++) {
    int x;
    cin >> x;
    f[x]++;
  }
  

  int count = 0;
  int ans = 0;
  for(int i = 0; i < n; i++) {
    int old = g[a[i]];
    g[a[i]]++;
    if(f.find(a[i]) != f.end()) {
      count -= min(old, f[a[i]]);
      count += min(g[a[i]], f[a[i]]);
    }
    if(i + 1 < m) continue;
    if(count >= k) ans++;

    old = g[a[i - m + 1]];
    g[a[i - m + 1]]--;
    if(f.find(a[i - m + 1]) != f.end()) {
      count -= min(old, f[a[i - m + 1]]);
      count += min(f[a[i - m + 1]], g[a[i - m + 1]]);
    }
  }
  cout << ans << endl;

}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
