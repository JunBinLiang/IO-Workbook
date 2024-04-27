#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector


void solve() {
  int n; ll k;
  cin >> n >> k;
  vector<int> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }
  
  //for(int i = 0; i < n; i++) cout << a[i] << " ";
  //cout << endl;

  int l = 0, r = n - 1;
  while(k > 0 && l <= r) {
    while(l < n && a[l] == 0) l++;
    while(r >= 0 && a[r] == 0) r--;
    if(l == r) {
      if(k >= a[l]) {
        cout << n << endl;
      } else {
        cout << n - 1 << endl;
      }
      return;
    }
    if(l > r) {
        cout << n << endl;
        return;
    }
    
    int mn = min(a[l], a[r]);
    //cout << k << " " << l << " " << r << endl;
    // for(int i = 0; i < n; i++) cout << a[i] << " ";
    // cout << endl << endl;
    if(k > 2 * mn) {
      k -= 2 * mn;
      a[l] -= mn;
      a[r] -= mn;
      continue;
    } else {
      if(k == 2 * mn) {
        k = 0;
        a[l] -= mn;
        if(a[l] == 0) l++;
        a[r] -= mn;
        if(a[r] == 0) r--;
      } else {
        if(k == 2 * mn - 1) {
            if(a[l] <= a[r]) {
                l++;  
            } 
        }
        k = 0;
      }
    }
  }
  cout << n - (r - l + 1) << endl;
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
