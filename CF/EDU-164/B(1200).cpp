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


void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for(int i = 0; i < n; i++) cin >> a[i];

  set<int> s(a.begin(), a.end());
  if(s.size() == 1) {
    cout << -1 << endl;
    return;
  }

  int ans = n;
  for(int i = 0; i < n; i++) {
    if(a[i] != a[0]) continue;
    int j = i;
    while(j < n && a[i] == a[j]) {
      j++;
    }
    ans = min(ans, j - i);
    i = j - 1;
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

