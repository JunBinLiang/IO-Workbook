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

int c = 0;

void solve() {
  int n;
  scanf("%d", &n);
  vector<int> a(n);
  ll l = 0, r = 0;
  ll tot = 0;
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    r += a[i];
    tot += a[i];
  }

  sort(a.begin(), a.end());

  ll ans = -1;
  while(l <= r) {
    ll mid = l + (r - l) / 2;
    ll s = 0;
    ll remain = tot;
    int use = 0;
    for(int i = n - 1; i >= 0 && s < mid; i--) {
      if(a[i] == 1 || mid - s == 1) break;
      if(s + a[i] <= mid) {
        s += a[i];
        remain -= a[i];
        use++;
      } else {
        use++;
        remain -= ((mid - s));
        s = mid;
        break;
      }
    }
    
    if(remain > mid && s != mid) {
        int need = remain - mid;
        if(s + need <= mid) {
            remain -= need;
            use += need;
        }
    }
    
    if(remain <= mid) {
      //cout << mid << " " << use << " " << remain << endl;
      ans = (use + mid);
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  
  printf("%lld\n", ans);

}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
