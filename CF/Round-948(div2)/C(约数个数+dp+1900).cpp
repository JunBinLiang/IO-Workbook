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

long long LCM(long long x, long long y) {
  return x / __gcd(x, y) * y;
}

//4:33 - 5 : 00
void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }

  sort(a.begin(), a.end());
  set<int> s(a.begin(), a.end());

  unordered_map<long long, int> pre;
  pre[a[0]] = 1;
  for(int i = 1; i < n; i++) {
    unordered_map<long long, int> cur;
    cur[a[i]] = 1;
    for(auto it = pre.begin(); it != pre.end(); it++) {
      long long v = it -> first;
      int count = it -> second;
      long long lcm = LCM(v, a[i]);
      if(a.back() % lcm != 0) {
        cout << n << endl;
        return;
      }
      if(cur.find(lcm) == cur.end()) cur[lcm] = count + 1;
      else cur[lcm] = max(cur[lcm], count + 1);
    }
    for(auto it = pre.begin(); it != pre.end(); it++) {
      long long v = it -> first;
      int count = it -> second;
      if(cur.find(v) == cur.end()) cur[v] = count;
      else cur[v] = max(cur[v], count);
    }
    pre = cur;
  }
  
  int ans = 0;
  for(auto it = pre.begin(); it != pre.end(); it++) {
    int v = (int)(it -> first);
    int count = it -> second;
    if(s.find(v) == s.end()) {
      ans = max(ans, count);
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
