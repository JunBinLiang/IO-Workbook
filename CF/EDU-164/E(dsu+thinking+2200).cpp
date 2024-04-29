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

//9:25 - 9: 50
const int N = 1e5 + 10;
ll ans[N];
int a[N];
bool vis[N];
int alive[N];
void solve() {
  int n;
  scanf("%d", &n);
  int mx = 0;
  vector<pair<int, int>> b;
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    mx = max(mx, a[i]);
    b.push_back({a[i], i});
  }

  memset(vis, 0, sizeof vis);
  sort(b.begin(), b.end());
  reverse(b.begin(), b.end());
  int j = 0;
  int component = 0;
  for(int i = mx; i >= 1; i--) {
    while(j < b.size() && i + 1 <= b[j].first) {
      int index = b[j].second;
      component++;
      vis[index] = true;
      if(index - 1 >= 0 && vis[index - 1]) component--;
      if(index + 1 < n && vis[index + 1]) component--;
      j++;
    }
    alive[i] = component; //how many connect component alive after i damage
  }
  
  //for(int i = 1; i <= mx; i++) cout << alive[i] << " ";
  //cout << endl << endl;


  memset(ans, 0, sizeof ans);
  ans[mx] = 1;
  for(int i = 1; i < mx; i++) {
    ans[i] = 1;
    for(int j = i; j <= mx; j += i) { //total damage
      ans[i] += alive[j];
    }
  }

  for(int i = 1; i <= mx; i++) {
    printf("%lld ", ans[i]);
  }
  printf("\n");
}

int main(){
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}

