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

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector


void verify(vector<vector<int>>& a, int k) {
  int sum = 0;
  int n = a.size();
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      sum += a[i][j];
    }
  }

  if(sum != k) {
    cout << "Fail" << endl;
    return;
  }

  set<int> s;
  for(int i = 0; i < n; i++) {
    int xo = 0;
    for(int j = 0; j < n; j++) xo ^= a[i][j];
    s.insert(xo);
  }

  if(s.size() != 1) {
    cout << "Fail" << endl;
    return;
  }

  s.clear();
  for(int i = 0; i < n; i++) {
    int xo = 0;
    for(int j = 0; j < n; j++) {
      xo ^= a[j][i];
    }
    s.insert(xo);
  }

  cout << "Success" << endl;
}

void solve() {
  int n, k;
  cin >> n >> k; //n, k even
  int K = k;

  if(k % 2 == 1) {
    cout << "No" << endl;
    return;
  }

  if(n == 2 && k == 2) {
    cout << "Yes" << endl;
    cout << "1 1" << endl;
    cout << "0 0" << endl;
    return;
  }

  if(k == 2 || k == n * n - 2) {
    cout << "No" << endl;
    return;
  }
  
  if(k == n * n) {
      cout << "Yes" << endl;
      for(int i = 0; i < n; i++) {
          for(int j = 0; j < n; j++) {
              cout << "1 ";
          }
          cout << endl;
      }
      return;
  }
  
  //gcd(4, 6) == 12
  vector<vector<int>> a(n, vector<int>(n));
  for(int i = 0; i < n && k > 6; i += 2) {
    for(int j = 0; j < n && k > 6; j += 2) {
      if(i < 4 && j < 4) continue;
      k -= 4;
      a[i][j] = a[i][j + 1] = a[i + 1][j] = a[i + 1][j + 1] = 1;
    }
  }

  if(k == 4) {
    a[0][0] = a[0][1] = a[1][0] = a[1][1] = 1;
  } else if(k == 8) {
    a[0][0] = a[0][1] = a[1][0] = a[1][1] = 1;
    a[2][0] = a[2][1] = a[3][0] = a[3][1] = 1;
  }
  else if(k == 6) {
    a[0][1] = a[0][2] = a[1][0] = a[1][2] = a[2][0] = a[2][1] = 1;
  } else if(k == 10) {
    a[0][1] = a[0][2] = a[1][0] = a[1][2] = a[2][0] = a[2][1] = 1;
    a[2][2] = a[2][3] = a[3][2] = a[3][3] = 1;
  } else if(k == 12) {
    a[0][0] = a[0][1] = a[1][0] = a[1][1] = 1;
    a[2][0] = a[2][1] = a[3][0] = a[3][1] = 1;
    a[0][2] = a[0][3] = a[1][2] = a[1][3] = 1;
  }
  

  //verify(a, K);

  cout << "Yes" << endl;
  for(auto& row : a) {
    for(int x : row) cout << x << " ";
    cout << endl;
  }

}

/*
10
0 1 1 0 
1 0 1 0 
1 1 1 1 
0 0 1 1 

6
0 1 1 0 
1 0 1 0 
1 1 0 0 
0 0 0 0 
*/

  

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
