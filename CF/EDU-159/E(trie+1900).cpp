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

const int N = 1e6 + 10;
int tr[N][26], cnt[N];
int id = 1;
void add(string& s) {
  int u = 0;
  for(int i = 0; i < s.size(); i++) {
    int c = s[i] - 'a';
    if(tr[u][c] == -1) {
      tr[u][c] = id++;
    }
    u = tr[u][c];
    cnt[u]++;
  }
}

void solve() {
  int n;
  cin >> n;
  vector<string> a(n);
  int tot = 0;
  for(int i = 0; i < n; i++) {
    cin >> a[i];
    tot += a[i].size();
  }

  memset(tr, -1, sizeof tr);
  memset(cnt, 0, sizeof cnt);
  for(int i = 0; i < n; i++) {
    string s = a[i];
    add(s);
  }

  ll ans = 0;
  for(int i = 0; i < n; i++) {
    string s = a[i];
    ans += (tot);
    ans += ((n + 0ll) * s.size());
    int u = 0;
    reverse(s.begin(), s.end());
    for(int j = 0; j < s.size() && u != -1; j++) {
      int d = s[j] - 'a';
      u = tr[u][d];
      if(u != -1) ans -= 2 * cnt[u];
    }
  }

  cout << ans << endl;
}


int main(){
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
