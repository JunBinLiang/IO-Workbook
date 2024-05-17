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



void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  vector<pair<int, int>> b;
  for(int i = 0; i < n; i++) {
    cin >> a[i];
    b.push_back({a[i], i});
  }
  sort(b.begin(), b.end());

  vector<pair<int, int>> ans1(n);
  vector<int> ans2(n);
  vector<int> indexs;
  int lasty = 1, lastindex = -1;
  for(int i = 0; i < n; i++) {
    int j = i;
    while(j < n && b[j].first == b[i].first) {
      int d = b[j].first, index = b[j].second;
      if(d == 0) { //first run
        ans1[index] = {j + 1, 1};
        ans2[index] = index;
        lastindex = index;
      } else {
        if(lasty == 1) {
          lasty = d;
          ans1[index] = {j + 1, lasty};
          ans2[index] = lastindex;
          if(lasty == 1) {
            lastindex = index;
          }
        } else {
          if(i == j) {
            lasty += (d - b[i - 1].first - 1);
            //cout << d << " " << b[i - 1].first << endl;
            ans1[index] = {j + 1, lasty};
            ans2[index] = lastindex;
          } else {
            lasty--;
            ans1[index] = {j + 1, lasty};
            ans2[index] = lastindex;
          }
          if(lasty == 1) {
            lastindex = index;
          }
        }
      }
      indexs.push_back(index);
      j++;
    }
    i = j - 1;
  }

  cout << "YES" << endl;
  for(auto& p : ans1) cout << p.first << " " << p.second << endl;
  for(int x : ans2) cout << x + 1 << " ";
  cout << endl;
}

int main(){
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
