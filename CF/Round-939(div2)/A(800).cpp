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
  int n, m;
  scanf("%d%d", &n, &m);
  vector<int> a(n);
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }

  while(m--) {
    int x;
    scanf("%d", &x);
    int j = n - 1;
    while(j >= 0) {
      if(x < a[j]) j--;
      else {
        x -= (j + 1);
      }
    }
    printf("%d ", x);
  }
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
