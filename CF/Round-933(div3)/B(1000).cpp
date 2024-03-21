#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
void solve() {
  int n;
  cin >> n;
  vector<ll> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }

  for(int i = 1; i < n - 1; i++) {
    if(a[i - 1] < 0) {
      cout << "NO" << endl;
      return;
    }
    a[i] -= (a[i - 1] * 2);
    if(a[i] < 0) {
        cout << "NO" << endl;
        return;
    }
    a[i + 1] -= a[i - 1];
    a[i - 1] = 0;
  }
  
  if(a.back() == 0 && a[n - 2] == 0) cout << "YES" << endl;
  else cout << "NO" << endl;
}


int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}

