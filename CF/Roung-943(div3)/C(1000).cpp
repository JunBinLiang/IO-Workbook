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
  n--;
  vector<int> a(n);
  for(int i = 0; i < n; i++) cin >> a[i];

  vector<int> ans(n + 1);
  ans[0] = 501;
  for(int i = 0; i < n; i++) {
    ans[i + 1] = ans[i] + a[i];
  }

  for(int x : ans) cout << x << " ";
  cout << endl;
}
  

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
