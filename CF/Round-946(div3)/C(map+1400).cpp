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
  int n;
  cin >> n;
  vector<int> a(n);  
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }

  
  ll ans = 0;
  map<pair<int, int>, vector<int>> f;
  for(int i = 0; i < n - 2; i++) {
    int t1 = a[i], t2 = a[i + 1], t3 = a[i + 2];
    f[{t1, t2}].push_back(t3);
  }

  for(auto it = f.begin(); it != f.end(); it++) {
    auto v = it -> second;
    sort(v.begin(), v.end());
    int tot = v.size();
    for(int i = 0; i < v.size(); i++) {
      int j = i;
      int count = 0;
      while(j < v.size() && v[i] == v[j]) {
        j++;
        count++;
      }
      ans += ((tot - count + 0ll) * count);
      i = j - 1;
    }
  }

  f.clear();
  for(int i = 0; i < n - 2; i++) {
    int t1 = a[i], t2 = a[i + 1], t3 = a[i + 2];
    f[{t1, t3}].push_back(t2);
  }

  for(auto it = f.begin(); it != f.end(); it++) {
    auto v = it -> second;
    sort(v.begin(), v.end());
    int tot = v.size();
    for(int i = 0; i < v.size(); i++) {
      int j = i;
      int count = 0;
      while(j < v.size() && v[i] == v[j]) {
        j++;
        count++;
      }
      ans += ((tot - count + 0ll) * count);
      i = j - 1;
    }
  }

  f.clear();
  for(int i = 0; i < n - 2; i++) {
    int t1 = a[i], t2 = a[i + 1], t3 = a[i + 2];
    f[{t2, t3}].push_back(t1);
  }

  for(auto it = f.begin(); it != f.end(); it++) {
    auto v = it -> second;
    sort(v.begin(), v.end());
    int tot = v.size();
    for(int i = 0; i < v.size(); i++) {
      int j = i;
      int count = 0;
      while(j < v.size() && v[i] == v[j]) {
        j++;
        count++;
      }
      ans += ((tot - count + 0ll) * count);
      i = j - 1;
    }
  }

  
  cout << ans / 2 << endl;
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
