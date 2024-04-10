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


void solve() {
  int n, k;
  string s;
  cin >> n >> k >> s;
  vector<int> L(k), R(k);
  for(int i = 0; i < k; i++) {
    cin >> L[i];
    L[i]--;
  }
  for(int i = 0; i < k; i++) {
    cin >> R[i];
    R[i]--;
  }

  int m;
  cin >> m;
  vector<int> line(n + 1);
  while(m--) {
    int p; cin >> p;
    p--;
    int l = 0, r = k - 1;
    int i = -1;
    while(l <= r) {
      int mid = l + (r - l) / 2;
      if(p >= L[mid]) i = mid, l = mid + 1;
      else r = mid - 1;
    }

    int p1 = min(p, L[i] + R[i] - p), p2 = max(p, L[i] + R[i] - p);
    line[p1]++; line[p2 + 1]--;
  }

  for(int i = 1; i < line.size(); i++) {
    line[i] += line[i - 1];
  }

  for(int i = 0; i < k; i++) {
    int l = L[i], r = R[i];
    int sz = r - l + 1;
    for(int j = 0; j < sz / 2; j++) {
      if(line[j + l] % 2 == 1) {
        swap(s[j + l], s[r - j]);
      }
    }
  }
  cout << s << endl;
}


int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
