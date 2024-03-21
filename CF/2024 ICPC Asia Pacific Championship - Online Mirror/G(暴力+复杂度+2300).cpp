#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)

vector<int> p[26][3010];
void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<string> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }

  for(int i = 0; i < n; i++) {
    string& s = a[i];
    vector<int> count(i, 0);  
    for(int j = 0; j < m; j++) {
      if(s[j] == '.') continue;
      
      for(int pos : p[s[j] - 'A'][j]) {
        count[pos]++;
      }
      p[s[j] - 'A'][j].push_back(i);
    }

    for(int j = i - 1; j >= 0; j--) {
      if(count[j] >= k) {
        cout << j + 1 << " " << i + 1 << endl;
        return;
      }
    }
  }

  cout << -1 << endl;
}


int main(){
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}

