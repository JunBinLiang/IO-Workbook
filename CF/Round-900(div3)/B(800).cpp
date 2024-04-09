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
  int n;
  cin >> n;
  vector<int> ans(n);
  ans[0] = 1, ans[1] = 3;
  for(int i = 2; i < n; i++) {
    ans[i] = ans[i - 1] + 2;
  }

  for(int i : ans) cout << i << " ";
  cout << endl;
}


int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
