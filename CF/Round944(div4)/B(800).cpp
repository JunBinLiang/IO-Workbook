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
  for(int i = 1; i < s.size(); i++) {
    if(s[i] != s[i - 1]) {
      cout << "YES" << endl;
      swap(s[i], s[i - 1]);
      cout << s << endl;
      return;
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
