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
  vector<int> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }

  int mn = a[0];
  for(int i = 0; i < n; i++) mn = min(mn, a[i]);

  int index = -1;
  for(int i = 0; i < n; i++) {
    if(a[i] == mn) {
      index = i;
      break;
    }
  }

  bool ok = true;
  for(int i = index + 1; i < n; i++) {
    if(a[i] < a[i - 1]) {
      ok = false;
    }
  }

  if(!ok) {
    cout << -1 << endl;
    return;
  }
  cout << index << endl;
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
