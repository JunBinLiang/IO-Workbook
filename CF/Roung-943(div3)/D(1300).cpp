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



void solve() {
  int n, k, p1, p2;
  cin >> n >> k >> p1 >> p2;
  vector<int> a(n + 1), b(n + 1);
  for(int i = 1; i <= n; i++) cin >> a[i];
  for(int i = 1; i <= n; i++) cin >> b[i];

  ll s1 = 0, s2 = 0;
  ll sum1 = 0, sum2 = 0;
  
  for(int i = 1; i <= min(n, k); i++) {
    sum1 += b[p1];
    s1 = max(s1, sum1 + (k - i + 0ll) * b[p1]);
    p1 = a[p1];
  }

  for(int i = 1; i <= min(n, k); i++) {
    sum2 += b[p2];
    s2 = max(s2, sum2 + (k - i + 0ll) * b[p2]);
    p2 = a[p2];
  }


  if(s1 > s2) cout << "Bodya" << endl;
  else if(s1 < s2) cout << "Sasha" << endl;
  else cout << "Draw" << endl;
}
  

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
