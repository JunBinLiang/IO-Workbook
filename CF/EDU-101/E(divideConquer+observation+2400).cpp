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

const int N = 1e6 + 10;
int p[N];

int get(int l, int r) {
  return l == 0 ? p[r] : p[r] - p[l - 1];
}

void solve() {
  int n, k;
  string s;
  cin >> n >> k >> s;
  int oldK = k;
  string ans = "";
  while(k > 20) {
    k--;
    ans += "0";
  }

  for(int i = 0; i < n; i++) {
    if(s[i] == '1') p[i] = 1;
    if(i) p[i] += p[i - 1];
  }

  vector<bool> is((1 << k) + 5);
  for(int i = ans.size(); i + k - 1 < n; i++) {
    if(ans.size() != 0 && get(i - ans.size(), i - 1) != ans.size()) {
      continue;
    }
    int bit = 0;
    for(int j = i; j < i + k; j++) {
      if(s[j] == '1') bit = bit * 2 + 1;
      else bit = bit * 2;
    }
    cout << bit << endl;
    is[bit] = true;
  }

  int mask = (1 << k) - 1;
  for(int i = 0; i < (1 << k); i++) {
    int com = mask ^ i;
    if(is[com]) continue;
    cout << "YES" << endl;
    for(int j = k - 1; j >= 0; j--) {
      if(i & (1 << j)) ans += "1";
      else ans += "0";
    }
    cout << ans << endl;
    return;
  }   
  cout << "NO" << endl;
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
