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


char a[7][7];
int dp[7][2200];
int f[2200][1 << 7];

int change(int st, int r) {
  int count = 0;
  for(int i = 0; i < 7; i++) {
    if(st & (1 << i)) {
      if(a[r][i] == 'W') count++;
    } else {
      if(a[r][i] == 'B') count++;
    }
  }
  return count;
}


void init() {
  memset(f, -1, sizeof f);
  for(int pst = 0; pst < 2187; pst++) {
    vector<int> a(7, 0);
    int j = 0;
    int s = pst;
    while(s) {
      a[j++] = (s % 3);
      s /= 3;
    }
    reverse(a.begin(), a.end());

    for(int st = 0; st < (1 << 7); st++) {
      vector<int> b;
      for(int i = 0; i < 7; i++) {
        if(st & (1 << i)) b.push_back(1);
        else b.push_back(0);
      }
      bool ok = true;
      for(int i = 1; i < 6; i++) {
        if(a[i] == 2 && b[i - 1] == 1 && b[i + 1] == 1) {
          ok = false;
        }
      }
      if(!ok) continue;

      int newst = 0;
      for(int i = 0; i < 7; i++) {
        if(b[i] == 0) {
          newst *= 3;
        } else {
          if(i - 1 >= 0 && i + 1 < 7 && a[i - 1] > 0 && a[i + 1] > 0) newst = newst * 3 + 2;
          else newst = newst * 3 + 1;
        }
      }
      f[pst][st] = newst;
    }
  }
}


void solve() {
  for(int i = 0; i < 7; i++) {
    string s; cin >> s;
    for(int j = 0; j < 7; j++) {
      a[i][j] = s[j];
    }
  }
  
  const int INF = 1e9;
  for(int i = 0; i < 7; i++) {
    for(int j = 0; j < 2200; j++) {
      dp[i][j] = INF;
    }
  }


  for(int st = 0; st < (1 << 7); st++) {
    int newst = 0;
    int count = change(st, 0);
    for(int i = 0; i < 7; i++) {
      if(st & (1 << i)) {
        newst = newst * 3 + 1;
      } else {
        newst = newst * 3;
      }
    }
    dp[0][newst] = count;
  }
  
  for(int i = 1; i < 7; i++) {
    for(int pst = 0; pst < 2187; pst++) {
      for(int st = 0; st < (1 << 7); st++) {
        if(f[pst][st] != -1) {
          int newst = f[pst][st];
          int count = change(st, i);
          dp[i][newst] = min(dp[i][newst], count + dp[i - 1][pst]);
        }
      }
    }
  }

  int ans = INF;
  for(int i = 0; i < 2187; i++) {
    ans = min(ans, dp[6][i]);
  }
  cout << ans << endl;
}


int main(){
  int t = 1;
  init();
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}

