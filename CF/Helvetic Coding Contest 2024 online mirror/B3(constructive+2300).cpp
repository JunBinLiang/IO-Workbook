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
  if(b[0].first == 0) {
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
        j++;
      }
      i = j - 1;
    }
  } else {
    bool same = false;
    for(int i = 1; i < n; i++) {
      if(b[i].first == b[i - 1].first) same = true;
    }

    if(!same) {
      if(b.size() == 2) {
        cout << "NO" << endl;
        return;
      }
      for(int i = 0; i < n; i++) {
        int index = b[i].second;
        if(i < 2) {
          ans1[index] = {i + 1, 1};
          ans2[index] = b[i + 1].second;
        } else {
          ans1[index] = {i + 1, 2};
          ans2[index] = b[0].second;
        }
      }

    } else {
      int lasty = 1, lastindex = -1;
      int skip1 = -1, skip2 = -1;
      for(int i = 1; i < n; i++) {
        if(b[i].first == b[i - 1].first) {
          int index1 = b[i].second, index2 = b[i - 1].second;
          skip1 = i; skip2 = i - 1;
          int d = b[i].first;
          ans1[index1] = {1, d};
          ans1[index2] = {2, 1};
          ans2[index1] = index2;
          ans2[index2] = index1;
          lastindex = index2;
          lasty = 1;
          break;
        }
      }
      
      int j = 2;
      int pd = -1;
      for(int i = 0; i < n; i++) {
        if(i == skip1 || i == skip2) continue;
        int d = b[i].first, index = b[i].second; 
        if(lasty == 1) {
          lasty = d;
          ans1[index] = {j + 1, lasty};
          ans2[index] = lastindex;
          if(lasty == 1) {
            lastindex = index;
          }
        } else {
          if(d != pd) {
            lasty += (d - pd - 1);
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
        j++;
        pd = d;
      }
    }
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
