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
#include <random>
#include <chrono>

using namespace std;
using ll = long long;

void solve() {
  int x, y, k;
  cin >> x >> y >> k;

  while(k > 0) {
    int ops = y - (x % y);
    if(x == 1) {
      x += (k % (y - 1));
      x %= y;
      break;
    } else {
      if(k >= ops) {
        k -= ops;
        x += ops;
        while(x % y == 0) x /= y;
      } else {
        x += k;
        k = 0;
      }
    }
  }
  cout << x << endl;
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}


