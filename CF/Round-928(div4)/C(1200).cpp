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


const int N = 2e5 + 10;
int dp[N];

int f(int n) {
  int s = 0;
  while(n) {
    s += (n % 10);
    n /= 10;
  }
  return s;
}

void init() {
  int s = 0;
  for(int i = 1; i < N; i++) {
    s += f(i);
    dp[i] = s;
  }
}

void solve() {
  int n;
  cin >> n;
  cout << dp[n] << endl;
}

int main(){
  int t = 1;
  init();
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
