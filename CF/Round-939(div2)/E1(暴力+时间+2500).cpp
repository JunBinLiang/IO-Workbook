#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector


void dfs(vector<pair<int, int>>& a, int l, int r) {
  //cout << l << " " << r << endl;
  //for(int i = 0; i < a.size(); i++) cout << a[i].first << " ";
  //cout << endl;
    
  int sz = r - l + 1;
  if(sz <= 0) return;
  if(sz == 1) return;
  if(sz == 2) {
    a[r].first = 0;
    return;
  } else if(sz == 3) {
    int x = a[l].first, y = a[l + 1].first, z = a[l + 2].first;
    if(x >= y) {
        a[l + 1].first = 0;
        return;
    }
    
    y -= x;
    int t1 = y / x;
    int mo = y % x;
    
    ll first = y, last = y - t1 * x;
    ll tot = (first + last) * (t1 + 1) / 2;
    if(tot >= z) {
      a[l + 2].first = 0;
    }
    a[l + 1].first = 0;
    return;
  } else {
    int zeroIndex = -1;
    int count = 0;
    while(zeroIndex == -1 && count < 10000) {
      count++;
      for(int i = l; i < r; i++) {
        int j = i + 1;
        a[j].first = max(0, a[j].first - a[i].first);
        if(a[j].first == 0) {
          zeroIndex = j;
          break;
        }
      }
    }
    
    dfs(a, l, zeroIndex - 1);
    dfs(a, zeroIndex + 1, r);
  }
}

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }

  bool zero = false;
  while(!zero) {
    for(int i = 0; i < n && !zero; i++) {
      if(a[i] == 0) zero = true;
      int j = (i + 1) % n;
      a[j] = max(0, a[j] - a[i]);
    }
  }

  int p = -1;
  for(int i = 0; i < n; i++) {
    if(a[i] == 0) {
      p = i;
    }
  }
  
  vector<pair<int, int>> b;
  for(int i = p; i < n; i++) {
    b.push_back({a[i], i + 1});
  }
  for(int i = 0; i < p; i++) {
    b.push_back({a[i], i + 1});
  }
  
  /*for(int i = 0; i < b.size(); i++) cout << b[i].second << " ";
  cout << endl;
  for(int i = 0; i < b.size(); i++) cout << b[i].first << " ";
  cout << endl;
  cout << endl;*/

  for(int i = 0; i < b.size(); i++) {
    if(b[i].first == 0) continue;
    int j = i;
    while(j < b.size() && b[j].first > 0) {
      j++;
    }
    dfs(b, i, j - 1);
    i = j - 1;
  }
  
  vector<int> ans;
  for(int i = 0; i < n; i++) {
    if(b[i].first) ans.push_back(b[i].second);
  }
  sort(ans.begin(), ans.end());
  printf("%d\n", (int)(ans.size()));
  for(int x : ans) printf("%d ", x);
  printf("\n");

}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
