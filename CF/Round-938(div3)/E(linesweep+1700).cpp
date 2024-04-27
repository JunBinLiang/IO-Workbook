#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector

const int N = 510;
int a[N][N];


void solve() {
  int n;
  string s;
  cin >> n >> s;

  int ans = 0;
  for(int i = 1; i <= n; i++) {
    vector<int> line(n + 1);
    int sum = 0;
    for(int j = 0; j < s.size(); j++) {
      if(j + i - 1 >= s.size()) break;
      int d = s[j] - '0';
      sum += line[j];
      if((sum + d) % 2 == 0) {
        sum++;
        line[j]++;
        line[j + i]++;
      }
    }

    bool ok = true;
    sum = 0;
    for(int j = 0; j < s.size() && ok; j++) {
      sum += line[j];
      int d = s[j] - '0';
      if((sum + d) % 2 == 0) ok = false;
    }
    if(ok) ans = i;
  }

  cout << ans << endl;
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
