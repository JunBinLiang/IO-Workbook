#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector

void solve() {
  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  for(int i = 0; i < n; i++) cin >> a[i];
  for(int i = 0; i < n; i++) {
    vector<int> f(101);
    int mx = 0;
    for(int j = i; j < n; j++) {
      f[a[j]]++;
      int count = f[k];
      if(a[j] != k) mx = max(mx, f[a[j]]);
      if(count > mx) {
        cout << "YES" << endl;
        return;
      } 
    }
  }

  cout << "NO" << endl;
}


int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
