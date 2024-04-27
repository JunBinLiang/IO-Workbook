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

const int N = 510;
int a[N][N];


void solve() {
  vector<int> a(5);
  cin >> a[1] >> a[2] >> a[3] >> a[4];
  
  if(a[4] % 2 == 1) a[4]--;

  int ans = a[4] / 2;
  ans += a[1] / 2;
  ans += a[2] / 2;
  ans += a[3] / 2;
  int add = (a[1] % 2) + (a[2] % 2) + (a[3] % 2);
  if(add >= 3) {
    ans++;
  }


  cout << ans << endl;

}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
