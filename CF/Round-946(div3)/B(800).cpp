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
  int n;
  string s;
  cin >> n >> s;
  
  set<char> se;
  for(char c : s) se.insert(c);

  string t = "";
  for(auto c : se) {
    t += c;
  }

  int l = 0, r = t.size() - 1;
  map<char, char> f;
  while(l <= r) {
    f[t[l]] = t[r];
    f[t[r]] = t[l];
    l++;
    r--;
  }


  for(char& c : s) {
    c = f[c];
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
