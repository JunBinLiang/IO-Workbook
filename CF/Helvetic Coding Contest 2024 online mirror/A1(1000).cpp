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
  string s;
  cin >> s;
  int p = 0;
  vector<pair<int, int>> b;
  for(int i = 0; i < s.size(); i++) {
    b.push_back({p, -i});
    if(s[i] == '(') p++;
    else p--;
  }
  sort(b.begin(), b.end());
  for(int i = 0; i < b.size(); i++) {
    cout << s[-b[i].second];
  }
}

int main(){
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
