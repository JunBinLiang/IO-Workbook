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
  int n;
  scanf("%d", &n);
  vector<int> count(n + 1);
  for(int i = 0; i < n; i++) {
    int x;
    scanf("%d", &x);
    count[x]++;
  }

  int two = 0, zero = 0;
  for(int i = 1; i <= n; i++) {
    if(count[i] == 2) {
      two++;
    } else if(count[i] == 0) {
      zero++;
    }
  }

  if(two > zero) {
    printf("%d\n", n - zero);
  } else {
    printf("%d\n", two);
  }
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
