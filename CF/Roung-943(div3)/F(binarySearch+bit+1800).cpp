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


int find(vector<int>& a, int L) {
  int l = 0, r = a.size() - 1;
  int p1 = -1;
  while(l <= r) {
    int mid = l + (r - l) / 2;
    if(a[mid] >= L) {
      p1 = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  return p1;
}

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<int> a(n);
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }

  int xo = 0;
  vector<int> p;
  map<int, vector<int>> f;
  for(int i = 0; i < n; i++) {
    xo ^= a[i];
    p.push_back(xo);
    f[xo].push_back(i);
  }

  while(m--) {
    int l, r;
    scanf("%d%d", &l, &r);
    l--; r--;
    int xo = p[r] ^ (l > 0 ? p[l - 1] : 0);
    if(xo == 0) { 
      cout << "YES" << endl;
    } else {
      int x = (l > 0 ? p[l - 1] : 0);
      if(f.find(xo ^ x) == f.end()) {
        cout << "NO" << endl;
        continue;
      }
      auto& v1 = f[xo ^ x];
      int p1 = find(v1, l);
      if(p1 == -1 || v1[p1] > r) {
        cout << "NO" << endl;
        continue;
      }
      if(f.find(x) == f.end()) {
        cout << "NO" << endl;
        continue;
      }
      auto& v2 = f[x];
      int p2 = find(v2, v1[p1] + 1);
      if(p2 == -1 || v2[p2] > r) {
        cout << "NO" << endl;
        continue;
      }
      cout << "YES" << endl;
    }
  } 
  //printf("\n");
}
  

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
