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
  int a, b, c;
  cin >> a >> b >> c;
  
  if(a * 2 + b != a + b + c - 1) {
    cout << -1 << endl;
    return;
  }

  int ans = 0;
  int lasta = 0, lastb = 0, lastc = 0;
  int s = a + b + c;
  for(int i = 0; i <= (s + 1) && (a > 0 || b > 0 || c > 0); i++) {
    int count = -1;
    if(i > 20) count = 2 * lasta + lastb;
    else count = min(1 << i, lasta * 2 + lastb);
    if(i == 0) count = 1;
    //cout << count <<" " << a << " " << b << " " << c << endl;
    ans = i;
    if(count >= a) {
      count -= a;
      lasta = a;
      a = 0;
    } else {
      lasta = count;
      a -= count;
      count = 0;
    }

    if(count >= b) {
      count -= b;
      lastb = b;
      b = 0;
    } else {
      lastb = count;
      b -= count;
      count = 0;
    }

    if(count >= c) {
      count -= c;
      lastc = c;
      c = 0;
    } else {
      lastc = count;
      c -= count;
      count = 0;
    }
    //cout << lasta << " " << lastb << " " << lastc << endl << endl;
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
