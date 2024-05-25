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
  int n, m;
  cin >> n >> m;
  int ans = 0;
  while(n > 0 && m > 0) {
    if(m >= 2) {
      m -= 2;
      n -= 7;
    } else {
      m--;
      n -= 11;
    }
    ans++;
  }

  if(m > 0) ans += ((m + 1) / 2);
  if(n > 0) {
    ans += n / 15;
    if(n % 15 != 0) ans++;
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
