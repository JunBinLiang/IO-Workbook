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


void solve() {
  ll n, k;
  cin >> n >> k;
  //1 3  5   7   9 11 13 15
  //2 6  10  14  18 22 26 30
  //4 12 20 28 36                 
  //8

  for(int i = 0; i < 30; i++) {
    ll start = (1 << i); //start term
    ll gap = start * 2;
    ll count = (n - start) / gap + 1;
    if(k > count) {
      k -= count;
    } else {
      cout << start + (k - 1) * gap << endl;
      break;
    }
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
