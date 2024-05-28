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


ll cal(vector<int>& a) {
  ll ans = a[0];
  ll s = 0;
  for(int i = 0; i < a.size(); i++) {
    s += a[i];
    ans = max(ans, s);
    if(s < 0) s = 0;
  }
  return ans;
}

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for(int i = 0; i < n; i++) cin >> a[i];

  ll ans = -10000000000000000ll;
  for(int i = 0; i < n; i++) {
    int j = i + 1;
    vector<int> cur;
    cur.push_back(a[i]);
    while(j < n && abs(a[j]) % 2 != abs(a[j - 1]) % 2) {
      cur.push_back(a[j]);
      j++;
    }
    ans = max(ans, cal(cur));
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
