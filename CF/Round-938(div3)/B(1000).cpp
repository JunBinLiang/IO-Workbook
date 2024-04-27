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

bool same(vector<int>& b, vector<int>& c) {
  for(int i = 0; i < b.size(); i++) {
    if(b[i] != c[i]) return false;
  }
  return true;
}

void solve() {
  int n, c, d;
  cin >> n >> c >> d;
  vector<int> b(n * n);
  for(int i = 0; i < n * n; i++) {
    cin >> b[i];
  }
  sort(b.begin(), b.end());
  a[0][0] = b[0];
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      if(i - 1 >= 0) a[i][j] = a[i - 1][j] + c;
      if(j - 1 >= 0) a[i][j] = a[i][j - 1] + d;
    }
  }
  

  vector<int> v;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      v.push_back(a[i][j]);
    }
  }
  
  sort(v.begin(), v.end());
  if(!same(b, v)) cout << "NO" << endl;
  else cout << "YES" << endl;
  
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
