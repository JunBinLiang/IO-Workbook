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

pair<int, int> convert(int i, int n) {
  if(i <= n) {
    return {i, 1};
  }
  return {n, i - n + 1};
}

void solve() {
  int n;
  cin >> n;
  if(n == 1) {
    cout << 1 << " " << 1 << endl;
    return;
  }

  
  vector<pair<int, int>> ans;
  ans.push_back(convert(1, n));
  ans.push_back(convert(2 * n - 1, n));

  int p = 2;
  for(int i = 2; i < n - 1; i++) {
    ans.push_back(convert(p, n));
    p++;
  }
  if(n > 2) {
    p--;
    ans.push_back(convert(p + 3, n));   
  }

  for(auto& p : ans) cout << p.first << " " << p.second << endl;
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
