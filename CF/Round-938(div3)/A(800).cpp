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
  ll n, a, b;
  cin >> n >> a >> b;
  if(a * 2 < b) cout << n * a << endl;
  else {
    cout << (n / 2) * b + (n % 2) * a << endl;
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
