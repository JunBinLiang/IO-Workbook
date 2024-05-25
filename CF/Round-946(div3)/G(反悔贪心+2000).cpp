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

//4:40 - 4:46
void solve() {
  int n, x;
  cin >> n >> x;
  vector<int> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }

  int cur = 0;
  int ans = 0;
  priority_queue<int> pq;
  for(int i = 0; i < n; i++) {
    if(cur >= a[i]) {
      cur -= a[i];
      pq.push(a[i]);
      ans++;
    } else {
      if(pq.size() > 0 && pq.top() > a[i]) {
        int top = pq.top(); pq.pop();
        cur += top; cur -= a[i];
        pq.push(a[i]);
      }
    }
    cur += x;
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
