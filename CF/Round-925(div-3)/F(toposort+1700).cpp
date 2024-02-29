#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
#include <string.h>

using namespace std;  
using ll = long long;

//7:15 - 7 : 21
void solve() {
  int n, k;
  cin >> n >> k;
  vector<vector<int>> g(n + 1, vector<int>(0));
  vector<int> in(n + 1);
  for(int i = 0; i < k; i++) {
    vector<int> ord(n);
    for(int j = 0; j < n; j++) {
      cin >> ord[j];
    }
    for(int j = 2; j < n; j++) {
      g[ord[j - 1]].push_back(ord[j]);
      in[ord[j]]++;
    }
  }

  int cnt = 0;
  queue<int> q;
  for(int i = 1; i <= n; i++) {
    if(in[i] == 0) {
      q.push(i);
    }
  }

  while(q.size() > 0) {
    int u = q.front(); q.pop();
    cnt++;
    for(int nxt : g[u]) {
      in[nxt]--;
      if(in[nxt] == 0) q.push(nxt);
    }
  }

  cout << (cnt == n ? "YES" : "NO") << endl;
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}

