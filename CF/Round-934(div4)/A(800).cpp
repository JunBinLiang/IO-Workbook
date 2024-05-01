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
  int a, b, c;
  cin >> a >> b >> c;
  if(a < b && b < c) {
    cout << "STAIR" << endl;
  } else if(a < b && b > c) {
    cout << "PEAK" << endl; 
  } else {
    cout << "NONE" << endl;
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
