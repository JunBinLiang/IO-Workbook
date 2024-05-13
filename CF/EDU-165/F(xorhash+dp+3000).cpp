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

using ull = unsigned long long;
unsigned long long seed = 131;
unsigned long long rands(){return seed = (seed << 15) + (seed << 8) + (seed >> 3);}

const int INF = 2000;
const int N = 1010;
int n, k;
ull h[N];
unordered_map<ull, pair<int, int>> mp;
unordered_set<int> deleteSet[N];

void solve() {
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
      cin >> a[i];
    }

    for(int i = 0; i <= k; i++) {
      h[i] = rands();
    }
    
    ull p = 0;
    for(int i = 1; i <= k; i++) {
      p ^= h[i];
    }

    unordered_set<ull> s;
    for(int i = 1; i <= k; i++) {
      for(int j = i + 1; j <= k; j++) {
        ull st = p ^ h[i] ^ h[j]; 
        s.insert(st);
        mp[st] = {i, j};
      }
    }
    
    vector<int> f(k + 1);
    vector<int> oddCount(n);
    int odd = 0;
    for(int i = n - 1; i >= 0; i -= 2) {
      f[a[i]]++;
      if(f[a[i]] % 2 == 1) odd++;
      else odd--;
      f[a[i - 1]]++;
      if(f[a[i - 1]] % 2 == 1) odd++;
      else odd--;
      oddCount[i - 1] = odd;
    }
    
    vector<int> dp(n, INF);
    dp[n - 1] = k / 2;
    for(int i = 0; i <= k; i++) f[i] = 0;
    f[a[n - 1]]++;
    f[a[n - 2]]++;

    for(int i = n - 3; i >= 0; i -= 2) {
      for(int j = 0; j <= k; j++) deleteSet[j].clear();

      unordered_set<int> remain;
      for(int j = 1; j <= k; j++) {
        if(f[j] % 2 == 0) {
          remain.insert(j);
        }
      }

      int validPair = (remain.size()) * (remain.size() - 1) / 2;
      
      ull st = p;
      unordered_set<ull> firstVisit;
      for(int j = i + 2; j < n; j += 2) {
        st ^= h[a[j]];
        st ^= h[a[j - 1]];
        if(s.find(st) != s.end() && firstVisit.find(st) == firstVisit.end()) {
          firstVisit.insert(st);
          dp[i] = min(dp[i], 1 + dp[j]);
          pair<int, int> p = mp[st]; //what we delete from the beginning
          deleteSet[p.first].insert(p.second);
          deleteSet[p.second].insert(p.first);
          if(remain.find(p.first) != remain.end() && remain.find(p.second) != remain.end()) {
            validPair--;
          }
        }
      } 

      //if currently have k different and can go to the end:
      //p ^ x ^ y where x ^ y not in firstVisit
      //find p ^ x ^ y ^ posth[i + 1] such that mimimum coin to lost
      if(firstVisit.size() != s.size()) { //can go to last
        dp[i] = 2 + (remain.size() / 2);
        for(int x : remain) {
          if(deleteSet[x].size() != k - 1) {
            dp[i] = min(dp[i], (int)(1 + (remain.size() / 2)));
          }
        }
        if(validPair > 0) {
          dp[i] = min(dp[i], (int)(remain.size() / 2));
        }
      }
      
      f[a[i]]++;
      f[a[i - 1]]++;
    }

    ull st = 0;
    for(int i = 0; i < n; i += 2) {
      st ^= h[a[i]];
      st ^= h[a[i + 1]];
      if(st == p) {
        cout << n / 2 - dp[i + 1] << endl;
        return;
      }
    }
    cout << n / 2 - oddCount[0] / 2 << endl;
}

int main(){
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
