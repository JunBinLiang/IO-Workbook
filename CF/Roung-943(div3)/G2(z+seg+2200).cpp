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

/*void kill() {
  vector<int> a;
  for(int i = 0; i < 1000000; i++) a.push_back(i);
}*/

vector<int> getZ(string& s) {
  int n = s.size();
  vector<int> z(n);
  int L = 0, R = 0;
  for (int i = 1; i < n; i++) 
  {
    if (i > R) 
    {
      L = R = i;
      while (R < n && s[R - L] == s[R]) 
      {
        R++;
      }
        z[i] = R - L; 
        R--;
    } 
    else 
    {
      int k = i - L;
      if (z[k] < R - i + 1) 
      {
        z[i] = z[k];
      } 
      else 
      {
        L = i;
        while (R < n && s[R - L] == s[R]) 
        {
          R++;
        }
        z[i] = R-L; 
        R--;
      }
    }
  }
  return z;
}

const int MAX = 200000 + 100;
const int INF = 1e9;
struct Node {
  int l, r;
  int mn;
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, INF};
  tree[id * 2 + 2] = {mid + 1, r, INF};
  build(id * 2 + 1);
  build(id * 2 + 2);
}

void update(int id, int index, int val) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    tree[id].mn = val;
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(index <= mid) {
    update(left, index, val);
  } else {
    update(right, index, val);
  }
  tree[id].mn = min(tree[left].mn, tree[right].mn);
}

int query(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].mn;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query(left, s, e);
  } else if(s >= mid + 1) {
      return query(right, s, e);
  } else {
    return min(query(left, s, mid), query(right, mid + 1, e));
  }
}

const int N = 2e5 + 10;
char c[N];
void solve() {
  int n, L, R;
  scanf("%d%d%d", &n, &L, &R);
  scanf("%s", c);
  string s(n, 'c');
  for(int i = 0; i < n; i++) s[i] = c[i];
  
  /*string s = "";
  int n = 200000;
  for(int i = 0; i < n; i++) s += "a";
  int L = 1, R = n;*/

  //count number of time s[0 : i] occurs
  vector<int> z = getZ(s);  
  tree[0] = {0, n, INF};
  build(0);
  
  vector<pair<int, int>> b;
  for(int i = 0; i < n; i++) {
    b.push_back({z[i], i});
    update(0, i, i);
  }
  sort(b.begin(), b.end());
  
  
  //for(int i = 0; i < n; i++) cout << z[i] << " ";
  //cout << endl;

  vector<int> maxs(n + 1);
  int cnt = 0;
  int j = 0;
  for(int len = 1; len <= n; len++) {
    while(j < b.size() && b[j].first < len) {
      update(0, b[j].second, INF);
      j++;
    }
    int count = 1;
    int cur = len;
    while(cur < n) {
      int index = query(0, cur, n - 1);
      if(index > n) break;
      cur = index + len;
      count++;
    }
    maxs[count] = max(maxs[count], len);
  }
  
  for(int i = n - 1; i >= 0; i--) {
    if(i + 1 <= n) maxs[i] = max(maxs[i], maxs[i + 1]);
  }
  for(int i = L; i <= R; i++) {
    printf("%d ", maxs[i]);
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
