#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <list>
#include<fstream>
#include <bitset>

using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define P pair
#define V vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define FFOR(i, a, b) for (int i = a; i <= b; ++i)

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

const int N = 105, INF = 1e9;
int dp[N][N][N];
int a[N];
int n;

int c = 0;
int dfs(int i, int l, int r) { //最左还没覆盖， 最右已经覆盖
  if(i > n) {
    if(l > n && r >= n) return 0;
    return INF;
  }
  if(dp[i][l][r] != -1) {
    return dp[i][l][r];
  }
  int ans = INF;
  ans = min(ans, dfs(i + 1, l , r));
  int L = max(1, i - a[i] + 1), R = min(n, i + a[i] - 1);
  //左
  ans = min(ans, 1 + dfs(i + 1, (L <= l) ? max(r, i) + 1 : l, max(r, i)));
  //右
  ans = min(ans, 1 + dfs(i + 1, (i <= l) ? max(r, R) + 1 : l, max(r, R)));
  return dp[i][l][r] = ans;
}

void solve() {
  cin >> n;
  for(int i = 1; i <= n; i++) {
    cin >> a[i];
  }

  //init
  for(int i = 0; i <= n + 2; i++) {
    for(int j = 0; j <= n + 2; j++) {
      for(int k = 0; k <= n + 2; k++) {
        dp[i][j][k] = -1;
      }
    }
  }
  
  int ans = INF;
  for(int i = 1; i <= n; i++) {
    int l = max(1, i - a[i] + 1), r = min(n, i + a[i] - 1);
    if(l == 1) {
      ans = min(ans, 1 + dfs(i + 1, i + 1, i));
    } else {
      ans = min(ans, 1 + dfs(i + 1, 1, i));
    }
    if(i == 1) {
      ans = min(ans, 1 + dfs(i + 1, r + 1, r));
    } else {
      ans = min(ans, 1 + dfs(i + 1, 1, r));
    }
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

