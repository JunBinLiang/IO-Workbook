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
  int n, h;
  cin >> h >> n;
  vector<int> a(n), c(n);
  for(int i = 0; i < n; i++) cin >> a[i];
  for(int i = 0; i < n; i++) {
    cin >> c[i];
    c[i]--;
  }

  long long l = 1, r = 1000000000000ll;
  long long ans = -1;
  while(l <= r) {
    long long mid = l + (r - l) / 2;
    long long sum = 0;
    for(int i = 0; i < n && sum < h; i++) {
      long long round = mid / (1 + c[i]);
      sum += (round * a[i]);
      if(mid % (1 + c[i]) != 0) sum += a[i];
    }
    if(sum >= h) {
      ans = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
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
