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

void solve() {
  int n, m;
  cin >> n >> m;
  if(n < m) {
    cout << "NO" << endl;
    return;
  }
  if((n - m) % 2 == 0) cout << "YES" << endl;
  else cout << "NO" << endl;
} 

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
