#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector

void solve() {
  string s;
  cin >> s;
  int h = (s[0] - '0') * 10 + (s[1] - '0');
  
  if(h < 12) {
    if(h == 0) {
        s[0] = '1';
        s[1] = '2';
    }
    s += " ";
    s += "AM";
  } else {
    if(h > 12) {
      h -= 12;
    }
    s[0] = (char)((h / 10) + '0');
    s[1] = (char)((h % 10) + '0');
    s += " ";
    s += "PM";
  }
  cout << s << endl;
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
