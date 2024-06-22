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

void solve() {
  int n, m;
  cin >> n >> m;
  vector<string> a(n);
  for(int i = 0; i < n; i++) cin >> a[i];

  int topr = n + 10, downr = -1;
  int leftc = m + 10, rightc = -1;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      if(a[i][j] == '#') {
        topr = min(topr, i + 1);
        downr = max(downr, i + 1);
        leftc = min(leftc, j + 1);
        rightc = max(rightc, j + 1);
      }
    }
  }
  cout << topr + (downr - topr) / 2 << " " << leftc + (rightc - leftc) / 2 << endl;
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
