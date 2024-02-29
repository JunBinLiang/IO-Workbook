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

//7:08 - 7 : 12
void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }
  
  int ans = n;
  int l = 0;
  while(l < n && a[0] == a[l]) l++;
  ans = min(ans, n - l);

  int r = n - 1;
  while(r >= 0 && a[r] == a.back()) r--;
  ans = min(ans, r + 1);

  if(a[0] == a.back() && l <= r) {
    ans = min(ans, r - l + 1);
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

