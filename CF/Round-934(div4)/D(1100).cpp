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

vector<int> a;
void init() {
  for(int i = 1; i < (1 << 5); i++) {
    int v = 0;
    for(int j = 0; j < 5; j++) {
      if(i & (1 << j)) v = v * 10 + 1;
      else v = v * 10;
    }
    if(v > 1)
        a.push_back(v);
  }
  a.push_back(100000);
}


void solve() {
  int n;
  cin >> n;
  for(int x : a) {
      while(n % x == 0) {
          n /= x;
      }
  }
  if(n == 1) cout << "YES" << endl;
  else cout << "NO" << endl;
}

int main(){
  init();
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
