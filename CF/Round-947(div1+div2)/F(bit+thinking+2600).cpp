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


const int N = 2e6 + 10;
int f[23][N];

int n;

void dfs(vector<int>& ans, int s, int i) {
  if(i < n) {
    int bit = 1 << (n - i - 1);
    for(int j = 0; j < bit; j++) f[i + 1][j] = f[i][j] & f[i][j | bit];
    dfs(ans, s * 2, i + 1);
    for(int j = 0; j < bit; j++) f[i + 1][j] = f[i][j] & (f[i][j | bit] >> 1);
    dfs(ans, s * 2 + 1, i + 1);
  } else {
    if(f[i][0] & 1) ans.push_back(s);
  }
}

void solve() {
  /*
  Understanding: 
  You are given 1-indexed based array a with length 2 ^ n - 1. Find all integer s such that
  for all index i where 1 <= i <= 2 ^ n - 1, 
  (a[i] & (1 << bitCount(s & i))) > 0 
  */
  scanf("%d", &n);
  for(int i = 1; i <= (1 << n); i++) {
    scanf("%d", &f[0][i]);
  }
  f[0][0] = 1;
  vector<int> ans;
  dfs(ans, 0, 0);
  sort(ans.begin(), ans.end());
  printf("%d\n", ans.size());
  for(int x : ans) printf("%d\n", x);
}

int main(){
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
