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

void solve() {
  int n;
  cin >> n;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      if((i + j) % 2 == 0) {
        cout << "##";
      } else {
        cout << "..";
      }
    }
    cout << endl;
    for(int j = 0; j < n; j++) {
      if((i + j) % 2 == 0) {
        cout << "##";
      } else {
        cout << "..";
      }
    }
    cout << endl;
  }
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
