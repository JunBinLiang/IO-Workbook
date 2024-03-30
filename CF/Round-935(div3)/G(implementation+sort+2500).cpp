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
#define ve vector

void solve() {
  int n, D;
  scanf("%d%d", &n, &D);
  vector<int> a(n), b(n);
  for(int i = 0; i < n; i++) {
    scanf("%d%d", &a[i], &b[i]);
  }

  priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pending; 
  priority_queue<vector<int>> available;
  int s = 0;
  vector<bool> vis(n);
  vector<pair<int, int>> suf;
  for(int i = n - 1; i >= 0; i--) {
    if(suf.size() == 0) {
      suf.push_back({a[i], i});
    } else {
      suf.push_back({max(a[i], suf.back().first), i});
    }
  }

  for(int i = 1; i <= D; i++) {
    while(pending.size() > 0 && pending.top()[0] < i) {
      int t = pending.top()[0];
      int j = pending.top()[1]; pending.pop();
      available.push({a[j], -t , -b[j], j});
    }

    vector<pair<int, int>> c;
    while(available.size() > 0 && available.top()[0] > suf.back().first) {
      int j = available.top()[3]; available.pop();
      c.push_back({a[j], j});
    }

    while(c.size() > 0) {
      suf.push_back(c.back()); c.pop_back();
    }
    
    //cout << "before" << endl;
    //for(auto& p : suf) cout << p.first << " " << p.second << endl;
    
    
    pair<int, int> p = suf.back(); suf.pop_back();
    
    //cout << "after" << endl;
    //for(auto& p : suf) cout << p.first << " " << p.second << endl;
    //cout << endl;
    
    int j = p.second;
    if(i + b[j] <= D) pending.push({i + b[j], j});
    if(!vis[j]) {
      s++;
      vis[j] = true;
    }    
    if(s == n) {
      cout << i << endl;
      return;
    }
  }

  cout << -1 << endl;
}


int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}

