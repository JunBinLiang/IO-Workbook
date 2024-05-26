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

int ask(int l, int x) {
  cout << "? " << l << " " << x << endl;
  int in;
  cin >> in;
  return in;
}

int mock(int l, int x) {
  cout << "? " << l << " " << x << endl;
  vector<int> a = {-1, 1, 3, 6, 1, 2, 1};
  int mx = 0;
  for(int i = l; i <= a.size(); i++) {
    mx = max(mx, a[i]);
    if(mx * (i - l + 1) == x) return i;
  }
  return a.size() + 1;
}

void solve() {
  int n, k;
  cin >> n >> k;
 
  int mx = 0;
  for(int i = n; i >= 1; i--) {
    if(ask(1, i * n) == n) { //find out the maximum
      mx = i;
      break;
    }
  }

  //answer = i * mx
  //n / k possible answer
  int ans = -1;
  for(int i = 1; i * k <= n ; i++) {
    int l = 1;
    bool ok = true;
    for(int j = 0; j < k; j++) {
      int r = ask(l, i * mx);
      if(r == n + 1) {
        ok = false;
        break;
      }
      l = r + 1;
      if(l == n + 1 && j != k - 1) {
          ok = false;
          break;
      }
    }
    if(ok && l == n + 1) {
      ans = max(ans, i * mx);
    }
  }

  cout << "! " << ans << endl;
  
  int end;
  cin >> end;
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
