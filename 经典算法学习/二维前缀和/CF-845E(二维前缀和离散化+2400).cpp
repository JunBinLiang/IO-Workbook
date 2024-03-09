#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <string.h>

using namespace std;  
using ll = long long;

const int N = 510 * 4;
pair<int, int> p[N];
int n, m, k;

int diff[N][N], mat[N][N];

//二维前缀和离散化
bool ok(int mid) {
  vector<int> x, y;
  x.push_back(1); x.push_back(n);
  y.push_back(1); y.push_back(m);
  x.push_back(0);
  y.push_back(0);
  x.push_back(n + 1);
  y.push_back(m + 1);
  for(int i = 0; i < k; i++) { //加点
    int r1 = max(1, p[i].first - mid), r2 = min(n, p[i].first + mid);
    int c1 = max(1, p[i].second - mid), c2 = min(m, p[i].second + mid);
    x.push_back(r1);
    x.push_back(r2);
    x.push_back(max(1, r1 - 1));
    x.push_back(min(n, r2 + 1));
    y.push_back(c1);
    y.push_back(c2);
    y.push_back(max(1, c1 - 1));
    y.push_back(min(m, c2 + 1));
  }

  sort(x.begin(), x.end());
  sort(y.begin(), y.end());
  unordered_map<int, int> f1, f2;
  vector<int> rev1(x.size() + 5), rev2(y.size() + 5);
  int id1 = 0, id2 = 0;
  for(int i = 0; i < x.size(); i++) {
    int j = i;
    while(j < x.size() && x[i] == x[j]) j++;
    f1[x[i]] = id1;
    rev1[id1] = x[i];
    id1++;
    i = j - 1;
  }

  for(int i = 0; i < y.size(); i++) {
    int j = i;
    while(j < y.size() && y[i] == y[j]) j++;
    f2[y[i]] = id2;
    rev2[id2] = y[i];
    id2++;
    i = j - 1;
  }

  memset(diff, 0, sizeof diff);
  for(int i = 0; i < k; i++) {
    int r1 = max(1, p[i].first - mid), r2 = min(n, p[i].first + mid);
    int c1 = max(1, p[i].second - mid), c2 = min(m, p[i].second + mid);
    int rr1 = f1[r1], rr2 = f1[r2];
    int cc1 = f2[c1], cc2 = f2[c2];
    int c21 = f2[c2 + 1];
    int r21 = f1[r2 + 1];
    diff[rr1][cc1]++;
    diff[rr1][c21]--;
    diff[r21][cc1]--;
    diff[r21][c21]++;
  }
  
  for(int i = f1[1]; i <= f1[n] ; i++) {
    for(int j = f2[1]; j <= f2[m]; j++) {
      mat[i][j] = diff[i][j];
      if(i - 1 >= 1) mat[i][j] += mat[i - 1][j];
      if(j - 1 >= 1) mat[i][j] += mat[i][j - 1];
      if(i - 1 >= 1 && j - 1 >= 1) mat[i][j] -= mat[i - 1][j - 1];
    }
  }
  
  int L = -1, R = -1, U = -1, D = -1;
  int length = 0;
  for(int i = f1[1]; i <= f1[n]; i++) {
    for(int j = f2[1]; j <= f2[m]; j++) {
      if(!mat[i][j]) {
        if(L == -1) {
          L = j;
          R = j;
        } else {
          L = min(L, j);
          R = max(R, j);
        }
        if(U == -1) {
          U = i;
          D = i;
        } else {
          D = i;
        }
      }
    }
        
  }
  if(L != -1) {
    length = max(length, (rev2[R + 1] - 1) - (rev2[L]) + 1);
  }
  if(U != -1) {
    length = max(length, (rev1[D + 1] - 1) - (rev1[U]) + 1);
  }
  
  return  mid * 2 + 1 >= length ;
}

void solve() {
  cin >> n >> m >> k;
  for(int i = 0; i < k; i++) {
    scanf("%d%d", &p[i].first, &p[i].second);
  }

  int l = 0, r = max(n, m), ans = -1;
  while(l <= r) {
    int mid = l + (r - l) / 2;
    if(ok(mid)) {
      ans = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  cout << ans << endl;
}

int main(){
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}

