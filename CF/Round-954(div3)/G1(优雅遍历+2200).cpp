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

const int N = 1e5 + 10;
vector<int> p[N];
void init() {
  for(int i = 1; i < N; i++) {
    for(int j = i; j < N; j += i) {
      p[j].push_back(i);
    }
  }
}

void solve() {
  int n;
  scanf("%d", &n);
  vector<int> a(n + 1);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }

  unordered_map<int, unordered_map<int, int>> f;
  long long ans = 0;
  for(int i = 1; i <= n; i++) {
    int g = __gcd(a[i], i);
    int x2 = a[i] / g, y2 = i / g;
    for(int y1 : p[x2]) {
      if(f.find(y1) != f.end() && f[y1].find(y2) != f[y1].end()) {
        ans += f[y1][y2];
      }
    }

    for(int d : p[x2]) {
      f[y2][d]++;
    }
  }
  printf("%lld\n", ans);
}

int main(){
  init();
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}


