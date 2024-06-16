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
#include <random>
#include <chrono>

using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)

const int MOD = 998244353;

void ADD(long long& x, long long y) {
  x += y;
  x %= MOD;
}

void solve() {
  int n, m;
  string s;
  cin >> n >> m >> s;
  s = "P" + s + "S";
  vector<long long> b(n + 2);
  for(int i = 1; i <= n; i++) cin >> b[i];

  //PP or SS, we can defined a[i]
  //PS, we know the sum
  set<long long> uni;
  for(int i = 0; i < b.size() - 1; i++) {
    long long s = b[i] + b[i + 1];
    uni.insert(s);
  }

  vector<long long> sums(uni.begin(), uni.end());
  long long ans = 0;
  for(long long w : sums) {
    vector<vector<long long>> dp(n + 2, vector<long long>(2, 0));
    dp[0][0] = 1;
    for(int i = 1; i <= n + 1; i++) {
      if(s[i] != 'S') { //P
        if(abs(b[i] - b[i - 1]) <= m) ADD(dp[i][0], dp[i - 1][0]);
        if(abs(b[i] + b[i - 1] - w) <= 2 * m) ADD(dp[i][0], dp[i - 1][1]);
      }
      if(s[i] != 'P') { //'S'
        if(abs(b[i - 1] - b[i]) <= m) ADD(dp[i][1], dp[i - 1][1]);
        if(b[i - 1] + b[i] == w) ADD(dp[i][1], dp[i - 1][0]);
      }
    }
    ADD(ans, dp[n + 1][1]);
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
