#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
#include <string.h>

using namespace std;  
using ll = long long;

bool same(int a, int b, int c, int d) {
  if(a > b) swap(a, b);
  if(c > d) swap(c, d);

  return a == c && b == d;
}

void solve() {
  int n, m;
  cin >> n >> m;

  if(n % 2 == 0) {
    int newn = n / 2, newm = m * 2;
    if(!same(n, m, newn, newm)) {
      cout << "YES" << endl;
      return;
    }
  }

  if(m % 2 == 0) {
    int newn = n * 2, newm = m / 2;
    if(!same(n, m, newn, newm)) {
      cout << "YES" << endl;
      return;
    }
  }

  cout << "NO" << endl;
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
