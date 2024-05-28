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

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for(int i = 0; i < n; i++) cin >> a[i];
  
  //(i, j) => a[i] * (2 ^ a[j])    ==   a[j] * (2 ^ a[i])
  //a[i] / (2 ^ a[i]) == a[j] / (2 ^ a[])
  ll ans = 0;
  map<pair<int, int>, int> f;
  for(int i = 0; i < n; i++) {
    int up = a[i], down = a[i];
    while(up % 2 == 0 && down > 1) {
      up /= 2;
      down--;
    }
    ans += f[{up, down}];
    f[{up, down}]++;
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
