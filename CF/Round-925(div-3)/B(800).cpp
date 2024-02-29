#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
#include <string.h>

using namespace std;  
using ll = long long;

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  ll sum = 0;
  for(int i = 0; i < n; i++) {
      cin >> a[i];
      sum += a[i];
  }
  ll t = sum / n;
  ll cur = 0;
  for(int i = 0; i < n; i++) {
      if(a[i] >= t) cur += (a[i] - t);
      else {
          if(cur < t - a[i]) {
              cout << "NO" << endl;
              return;
          }
          cur -= (t - a[i]);
      }
  }
  cout << "YES" << endl;
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}

