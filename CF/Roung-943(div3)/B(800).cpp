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
  string s, t;
  cin >> n >> m >> s >> t;
  int j = 0;
  int ans = 0;
  for(int i = 0; i < s.size(); i++){
    while(j < m && t[j] != s[i]) j++;
    if(j < m && s[i] == t[j]) {
      ans = i + 1;
      j++;
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
