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

/*void kill() {
  vector<int> a;
  for(int i = 0; i < 1000000; i++) a.push_back(i);
}*/

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }

  int ans = 3;
  for(int i = 0; i < n; i++) {
    // i come
    for(int j = i + 1; j < n; j++) {
      if(a[j] == i + 1 && a[i] == j + 1) {
        ans = 2;
      }
    }
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
