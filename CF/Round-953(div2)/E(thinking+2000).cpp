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
//6:30 - 6:58
const int N = 2e5 + 10, INF = 1e9;
int p[N], pp[N];
pair<int, int> in[N];

int get(int l, int r) {
  return l == 0 ? p[r] : p[r] - p[l - 1];
}

int get1(int l, int r) {
  return l == 0 ? pp[r] : pp[r] - pp[l - 1];
}

void solve() {
  int n, m;
  string s, t;
  cin >> n >> s >> t;
  for(int i = 0; i <= n; i++) {
    p[i] = pp[i] = 0;
    in[i] = {-1, -1};
  }

  int sum = 0;
  for(int i = 0; i < n; i++) {
    if(s[i] == '1') sum++;
    p[i] = sum;
  }

  
  for(int i = 1; i < n - 1; i++) {
    if(s[i] == '1') continue;
    int l, r;
    if(t[i + 1] == '1') {
      r = i + 1;
    } else if(i + 2 < n && s[i + 2] == '0') {
      r = i + 2;
    } else {
      r = INF;
    }

    if(t[i - 1] == '1') {
      l = i - 1;
    } else if(i - 2 >= 0 && s[i - 2] == '0') {
      l = i - 2;
    } else {
      l = -1;
    }
    if(l == -1 || r == INF) continue;
    pp[i] = 1;
    in[i] = {l, r};
  }

  for(int i = 1; i < n; i++) {
    pp[i] += pp[i - 1];
  }
 
  scanf("%d", &m);
  for(int i = 0; i < m; i++) {
    int l, r;
    scanf("%d%d", &l, &r);
    
    l--; r--;
    int ans = get(l, r) + get1(l, r);
    int lcheck = -1;
    int cnt = 0;
    for(int j = l; j <= min(l + 3, r); j++) {
      lcheck = j;
      if(in[j].first == -1) continue;
      if(in[j].first < l || in[j].second > r) ans--;
    }

    for(int j = r; j > max(r - 3, lcheck); j--) {
      if(in[j].first == -1) continue;
      if(in[j].first < l || in[j].second > r) ans--;
    }
    
    printf("%d\n", ans);
  }
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
