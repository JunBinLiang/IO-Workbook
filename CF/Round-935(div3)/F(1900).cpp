#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector

void solve() {
  int n;
  cin >> n;
  vector<pair<int, int>> a(n);
  for(int i = 0; i < n; i++) cin >> a[i].second;
  for(int i = 0; i < n; i++) {
    cin >> a[i].first;
    a[i].first--;
  }

  ll ans = 0, count = 0;
  priority_queue<ll, vector<ll>, greater<ll> > pq;
  for(int i = n - 1; i >= 0; i--) {
    pq.push(a[a[i].first].second);
    ll take = i + 1;
    while(pq.size() > take) pq.pop();
    if(pq.size() == take) {
      ll v = (take) * (pq.top());
      if(v >= ans) {
        if(v > ans) {
          ans = v;
          count = take;
        } else {
          count = min(count, take);
        }
      }
    }
  }
  cout << ans << " " << count << endl;
}


int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
