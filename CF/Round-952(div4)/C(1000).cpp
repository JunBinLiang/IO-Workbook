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

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  long long sum = 0, ans = 0;
  set<long long> s;
  for(int i = 0; i < n; i++) {
    cin >> a[i];
    sum += a[i];
    s.insert(a[i]);
    if(sum % 2 == 0 && s.find(sum / 2) != s.end()) {
      ans++;
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
