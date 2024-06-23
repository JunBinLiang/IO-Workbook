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


void solve() {
  long long n, a, b;
  cin >> n >> a >> b;
  if(b < a) {
    cout << n * a << endl;
  } else {
    long long dif = b - a;
    long long useb = min(dif, n);
    cout << (n - useb) * a + ((b - useb + 1 + b) * useb / 2) << endl;  
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
