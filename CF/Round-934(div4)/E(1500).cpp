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
  string s;
  cin >> n >>  s;
  int ans = n;
  for(int i = 1; i <= n; i++) {
    if(n % i == 0) {
      int count = 0;
      for(int j = 0; j < n; j++) {
        count += (s[j] != s[j % i]);
      }
      if(count <= 1) {
        ans = min(ans, i);
        break;
      }
    }
  }
  
  reverse(s.begin(), s.end());
  for(int i = 1; i <= n; i++) {
    if(n % i == 0) {
      int count = 0;
      for(int j = 0; j < n; j++) {
        count += (s[j] != s[j % i]);
      }
      if(count <= 1) {
        ans = min(ans, i);
        break;
      }
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
