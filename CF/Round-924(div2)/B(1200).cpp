#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
#include <string.h>

using namespace std;  
using ll = long long;

void solve() {
  int n;
  cin >> n;
  set<int> s;
  for(int i = 0; i < n; i++) {
    int x;
    cin >> x;
    s.insert(x);
  }

  vector<int> a(s.begin(), s.end());
  int ans = 0;
  for(int i = 0, j = 0; i < a.size(); i++) {
    while(j < i && a[i] - a[j] > n - 1) {
      j++;
    }
    ans = max(ans, i - j + 1);
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
