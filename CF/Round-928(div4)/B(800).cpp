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
  bool square = true;
  int lastl = -1, lastr = -1;
  for(int i = 0; i < n; i++) {
    string s;
    cin >> s;
    int l = -1, r = -1;
    for(int j = 0; j < n; j++) {
      if(s[j] == '1') {
        if(l == -1) l = j;
        r = j;
      }
    }
    if(l == -1) continue;
    if(lastl == -1) {
      lastl = l;
      lastr = r;
    } else {
      if(l != lastl || r != lastr) {
        square = false;
      }
    }
  }
  if(square) cout << "SQUARE" << endl;
  else cout << "TRIANGLE" << endl;
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
