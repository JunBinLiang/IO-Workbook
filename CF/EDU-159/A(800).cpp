#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
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
  int one = 0, zero = 0;
  for(int i = 0; i < s.size(); i++) {
    if(s[i] == '0') zero++;
    else one++;
    if(i + 1 < n && s[i] != s[i + 1]) {
        cout << "YES" << endl;
        return;
    }
  }  

  if(zero > one) cout << "YES" << endl;
  else cout << "NO" << endl;

}


int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
