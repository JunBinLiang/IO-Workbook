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

const int N = 3e5 + 1;
bool isp[N];
vector<int> p;
void init() {
  if(p.size() > 0) return;
  memset(isp, 0, sizeof isp);
  for(int i = 2; i < N; i++) {
    if(isp[i]) continue;
    p.push_back(i);
    for(int j = i; j < N; j += i) {
      isp[j] = true;
    }
  }
}

//Complete Graph + Euler Pah
/* 

Find longest simple walk in a complete graph
https://cs.stackexchange.com/questions/45088/longest-simple-walk-in-a-complete-graph
- if n is odd, there is euler path, which is the longest path for visting every edge
  1/2 * n * (n - 1)
- if n is even,  delete a matching of size of (1 / 2 n - 1), to the remain graph is Euler. 1/2 * n * (n - 2) + 1

length of the path is defined as the number of nodes.
*/

set<int> g[N];
vector<int> path;
void dfs(int u) { //dfs to find euler path
  while(g[u].size() > 0) {
    auto it = g[u].begin();
    int v = *it;
    g[u].erase(v);
    g[v].erase(u);
    dfs(v);
  }
  path.push_back(u);
}

void euler(int n) {
  //find the euler path from node 0 to node n - 1
  int e = 0;
  for(int i = 0; i < n; i++) {
    for(int j = i + 1; j < n; j++) {
      g[i].insert(j);
      g[j].insert(i);
      e++;
    }
  }
  
  if(n % 2 == 0) {
    for(int i = 1; i < n - 2; i += 2) {
      int u = i, v = i + 1;
      g[u].erase(v);
      g[v].erase(u);
      e--;
    }
  }
  //欧拉dfs 要从单数点开始如果存在单数点
  dfs(0);
}

void solve() {
  init();
  path.clear();
  int n;
  scanf("%d", &n);

  int l = 1, r = p.size();
  int nodes = -1;
  while(l <= r) {
    int mid = l + (r - l) / 2;
    int count = mid;
    count += ((mid) * (mid - 1) / 2);
    if(mid % 2 == 1) {
    } else {
      count -= (mid / 2 - 1);
    }
    
    if(count >= n - 1) {
      nodes = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  
  euler(nodes);
  reverse(path.begin(), path.end());
  
  vector<int> ans;
  set<int> first;
  for(int i = 0; i < path.size(); i++) {
    ans.push_back(p[path[i]]);
    if(first.find(path[i]) == first.end()) {
      first.insert(path[i]);
      ans.push_back(p[path[i]]); //with itself
    }
  }
  
  for(int i = 0; i < min(n, (int)(ans.size())); i++) {
    printf("%d ", ans[i]);
  }
  printf("\n");
} 

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
