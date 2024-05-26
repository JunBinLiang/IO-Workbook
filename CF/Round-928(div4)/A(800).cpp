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
  int c1 = 0, c2 = 0;
  for(char c : s) {
    if(c == 'A') c1++;
    else c2++;
  }
  if(c1 > c2) cout << "A" << endl;
  else cout << "B" << endl;
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
