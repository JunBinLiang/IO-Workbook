#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)

//7:00 - : 7:30
int T;
void solve() {
  int n, m;
  cin >> n;
  vector<vector<int>> a(n, vector<int>(n));
   vector<vector<int>> b(n, vector<int>(n));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      cin >> a[i][j];
      b[i][j] = a[i][j];
    }
  }

  vector<int> row, col;
  vector<vector<int>> ans;
  for(int i = 0; i < n; i++) {
    vector<int> cnt1(n + 1), cnt2(n + 1);
    for(int j = 0; j < n; j++) {
      cnt1[a[i][j]]++;
      cnt2[a[j][i]]++;
    }

    bool check1 = false, check2 = false;
    for(int j = 1; j <= n; j++) {
      if(cnt1[j] > 1) {
        check1 = true;
      }
      if(cnt2[j] > 1) {
        check2 = true;
      }
    }
    if(!check1) {
      row.push_back(i);
    }
    if(!check2) {
      col.push_back(i);
    }
  }


  for(int i = 0; i < min(row.size(), col.size()); i++) {
    int r = row[i], c = col[i];
    vector<int> cnt1(n + 1), cnt2(n + 1);
    for(int j = 0; j < n; j++) {
      if(j == c) continue;
      cnt1[a[r][j]]++;
    }
    for(int j = 0; j < n; j++) {
      if(j == r) continue;
      cnt2[a[j][c]]++;
    }
    bool ok = false;
    for(int j = 1; j <= n; j++) {
      if(cnt1[j] && cnt2[j]) {
        ans.push_back({r, c, j});
        a[r][c] = j;
        ok = true;
        break;
      }
    }
    if(!ok) {
      a[r][c] += 1;
      if(a[r][c] > n) a[r][c] -= n;
      ans.push_back({r, c, a[r][c]});
    }
  }

  for(int i = 0; i < n; i++) {
    vector<int> cnt1(n + 1), cnt2(n + 1);
    for(int j = 0; j < n; j++) {
      cnt1[a[i][j]]++;
      cnt2[a[j][i]]++;
    }
 
    bool check1 = false, check2 = false;
    for(int j = 1; j <= n; j++) {
      if(cnt1[j] > 1) {
        check1 = true;
      }
      if(cnt2[j] > 1) {
        check2 = true;
      }
    }
    if(check1 && check2) continue;
    cnt1[a[i][i]]--;
    cnt2[a[i][i]]--;
    bool ok = false;
    for(int j = 1; j <= n; j++) {
      if(cnt1[j] && cnt2[j]) {
        ans.push_back({i, i, j});
        a[i][i] = j;
        ok = true;
        break;
      }
    }
    if(!ok) {
      a[i][i] += 1;
      if(a[i][i] > n) a[i][i] -= n;
      ans.push_back({i, i, a[i][i]});
    }
  }
  
  /*
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) cout << a[i][j] << " ";
    cout << endl;
  }*/

  cout << ans.size() << endl;
  for(auto& v : ans) {
    cout << v[0] + 1 << " " << v[1] + 1 << " " << v[2] << endl;
  }
}


int main(){
  int t = 1;
  cin >> t;
  T = t;
  while(t--) {
    solve();
  }
  return 0;
}

