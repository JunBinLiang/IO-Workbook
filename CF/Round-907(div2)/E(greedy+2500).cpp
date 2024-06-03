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

int gcd(int x, int y) {
  if(x == 0 || y == 0) {
    return x + y;
  }
  return __gcd(x, y);
}

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  vector<int> a(n);
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }

  vector<int> one;
  priority_queue <int, vector<int>, greater<int> > pq2; 
  priority_queue<int> pq1;
  int tot = 0;
  int s = 0;
  for(int i = 0; i < n; i++) {
    if(a[i] == 1) {
      int j = i;
      int count = 0;
      while(j < n && a[j] == 1) {
        j++;
        count++;
      }
      if(i == 0 || j == n) {
        s += count;
        tot += count;
      } else {
        tot += (count + 1);
        pq2.push(count);    
      }
      //cout << "one : " << count << endl;
      i = j - 1;
    } else {
      int j = i + 1;
      int count = 1;
      while(j < n && a[j] != 1 && gcd(a[j], a[j - 1]) == 1) {
        count++;
        j++;
      }
      if(count > 1) {
          pq1.push(count);
          tot += (count - 1);
      }
      //cout << "non : " << count << endl;
      i = j - 1;
    } 
  }
  
  if(s == n) { //all one
    printf("%d\n", n - k);
    return;
  }

  int ans = 0;
  while(k > 0) {
    if(pq1.size() > 0 && pq1.top() > 2) {
      int top = pq1.top(); pq1.pop();
      k--;
      top -= 2;
      ans += 2;
      if(top > 1) pq1.push(top);
    } else {
      if(pq2.size() > 0) {
        int top = pq2.top(); pq2.pop();
        if(k >= top) {
          k -= top;
          ans += (top + 1);
        } else {
          ans += k;
          k = 0;
        }
      } else {
        if(pq1.size() > 0) {
          int top = pq1.top(); pq1.pop();
          k--;
          ans++;
        } else {
          break;
        }
      }
    }
  }
  
  ans += min(s, k);
  printf("%d\n", tot - ans);
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
