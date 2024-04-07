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

void test(vector<int>& a, int x) {
  int l = 1, r = a.size();
  while(r - l != 1) {
    int m = (l + r) / 2;
    if(a[m] <= x) {
      l = m;
    } else {
      r = m;
    }
  }
  cout << a[l] << " " << x << endl;
}

void solve() {
  int n, x;
  cin >> n >> x;
  vector<int> a(n + 1);
  int pos = -1;
  for(int i = 1; i <= n; i++) {
    cin >> a[i];
    if(a[i] == x) pos = i;
  }

  vector<pair<int, int>> ans;
  swap(a[1], a[pos]);
  ans.push_back({1, pos});
  
  //for(int x : a) cout << x << " ";
  //cout << endl;
  
  //[l : r - 1]
  int l = 1, r = n + 1;
  while(r - l != 1) {
    int m = (l + r) / 2;
    if(a[m] <= x) {
      l = m;
    } else {
      r = m;
    }
  }
  

  if(l != 1) {
    ans.push_back({1, l});
    swap(a[1], a[l]);
  }
  //test(a, x);

  cout << ans.size() << endl;
  for(auto& p : ans) cout << p.first << " " << p.second << endl;
}


int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
