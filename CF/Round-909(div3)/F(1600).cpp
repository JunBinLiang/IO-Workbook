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
  vector<int> a(m);
  for(int i = 0; i < m; i++) {
    cin >> a[i];
  }

  //tree
  for(int i = 1; i < n; i++) {
    cout << i << " " << i + 1 << endl;
  }

  int last = n - 1;
  for(int i = 0; i < m; i++) {
    int d = a[i];
    if(d == last) {
      cout << "-1 -1 -1" << endl;
    } else {
      cout << n << " " << last << " " << d << endl;
      last = d;
    }
  }
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
