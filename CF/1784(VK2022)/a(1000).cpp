#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <string.h>

using namespace std;  
using ll = long long;

const int N = 2e5 + 10;
void solve() {
  int n;
  scanf("%d", &n);
  vector<int> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }

  sort(a.begin(), a.end());
  int to = 0;
  ll s = 0;
  for(int x : a) {
    if(to + 1 <= x) {
      to++;
    }
    s += (x - to);
  }
  cout << s << endl;

  //for(int i = 0; i < n; i++) {
    //printf("%lld ", ans[i]);
  //}
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

