#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>

using namespace std;  
using ll = long long;


void output(vector<string>& a, int k) {
  int n = a.size();
  vector<pair<int, string>> ans;
  for(int i = 0; i < n; i++) {
    int j = i, cnt = 0;
    while(j < n && a[i] == a[j]) {
      cnt++;
      j++;
    }

    string& s = a[i];
    int sz = s.size();
    if(k >= cnt * sz) {
      k -= cnt * sz;
      ans.push_back({cnt, s});
    } else {
      int c = k / sz, m = k % sz;
      if(c > 0) {
        ans.push_back({c, s});
      }
      if(m > 0) {
        ans.push_back({1, s.substr(0, m)});
      }
      break;
    }
    i = j - 1;
  }

  cout << "YES" << endl;
  cout << ans.size() << endl;
  for(auto p : ans) {
    cout << p.first << " " << p.second << endl;
  }
}

void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  if(k > 4 * n * m - 2 * (n + m)) {
    cout << "NO" << endl;
    return;
  }

  vector<string> ans;
  for(int i = 0; i < n - 1; i++) {
    for(int j = 0; j < m - 1; j++) {
      ans.push_back("R");
    }
    for(int j = 0; j < m - 1; j++) {
      ans.push_back("DUL");
    }
    ans.push_back("D");
  }

  for(int i = 0; i < m - 1; i++) {
    ans.push_back("R");
  }
  for(int i = 0; i < m - 1; i++) {
    ans.push_back("L");
  }
  for(int i = 0; i < n - 1; i++) {
    ans.push_back("U");
  }

  output(ans, k);
}

int main(){
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}

