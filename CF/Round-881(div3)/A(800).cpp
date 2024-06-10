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


void solve() {
   int n;
   cin >> n;
   vector<int> a(n);
   for(int i = 0; i < n; i++) cin >> a[i];
   sort(a.begin(), a.end());

   int ans = 0;
   int l = 0, r = n - 1;
   while(l <= r) {
    ans += (a[r--] - a[l++]);
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
