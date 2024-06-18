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
#include <random>
#include <chrono>

using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)

bool ask(int i, int j) {
  cout << "? " << i << " " << j << endl;
  string s;
  cin >> s;
  return s == "YES";
}

bool dfs(vector<vector<int>>& g, int u, int t) {
  if(u == t) return true;
  bool ans = false;
  for(int v : g[u]) {
    ans |= dfs(g, v, t);
  }
  return ans;
}

void output(vector<int>& ans) {
  cout << "! ";
  for(int i = 1; i < ans.size(); i++) cout << ans[i] << " ";
  cout << endl;
}

//////////////////////////////////////////////
vector<vector<int>> g(100);
bool mock(int i, int j) {
  if(dfs(g, j, i)) {
    cout << i << " " << j << " " << "YES" << endl;
    return true;
  } else {
    cout << i << " " << j << " " << "NO" << endl;
    return false;
  }
}
void read() {
    int m;
    cin >> m;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }
}
//////////////////////////////////////////////

void solve() {
  int n;
  cin >> n;
  
  //read();

  vector<vector<int>> stks(2);
  vector<int> both;
  stks[0].push_back(1);
  for(int i = 2; i <= n; i++) {
    if(stks[1].size() == 0) {
      if(ask(stks[0].back(), i)) stks[0].push_back(i);
      else stks[1].push_back(i);
    } else {
      if(both.size() > 0) {
          if(ask(both.back(), i)) {
            both.push_back(i);
          } else {
            bool x = ask(stks[0].back(), i);
            if(x) {
                stks[0].push_back(i);
                for(int v : both) stks[1].push_back(v);
                both.clear();
            } else {
                stks[1].push_back(i);
                for(int v : both) stks[0].push_back(v);
                both.clear();
            }
          }
          
      } else {
        bool x = ask(stks[0].back(), i);
        bool y = ask(stks[1].back(), i);
        if(x && y) {
            both.push_back(i);
        } else if(x) {
            stks[0].push_back(i);
        } else {
            stks[1].push_back(i);
        }
      } 
      
    }
  }
  
  /*cout << endl;
  for(int i : stks[0]) cout << i << " ";
  cout << endl;
  for(int i : stks[1]) cout << i << " ";
  cout << endl;
  for(int i : both) cout << i << " ";
  cout << endl;*/
  

  vector<int> ans(n + 1);
  if(stks[1].size() == 0) {
    ans[n] = 1;
  } else {
    for(int i : stks[1]) ans[i] = 1;
    for(int i : both) ans[i] = 1;
  }
  output(ans);
} 

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
