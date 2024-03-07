#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <set>
#include <string.h>

using namespace std;  
using ll = long long;

void solve() {
  int n, x;
  cin >> n >> x;

  //1 2 3 4 5 6 5 4 3 2
  //1 2 3 4 5 6 7 6 5 4 3 2
  int n1 = n - x;
  set<int> s;
  for(int i = 1; i * i <= n1; i++) {
    if(n1 % i == 0) {
      int a = i, b = n1 / i;
      if((a + 2) % 2 == 0 && (a + 2) / 2 >= x) s.insert(a);
      if(a != b && (b + 2) % 2 == 0 && (b + 2) / 2 >= x) s.insert(b);
    }
  }

  if(x > 1) {
    int n2 = n + (x - 2);
    for(int i = 1; i * i <= n2; i++) {
      if(n2 % i == 0) {
        int a = i, b = n2 / i;
        if((a + 2) % 2 == 0 && (a + 2) / 2 >= x) s.insert(a);
        if(a != b && (b + 2) % 2 == 0 && (b + 2) / 2 >= x) s.insert(b);
      }
    }

  }
  
  cout << s.size() << endl;
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
