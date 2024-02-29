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
  int n;
  cin >> n;
  for(int i = 0; i < 26; i++) {
    for(int j = 0; j < 26; j++) {
      for(int k = 0; k < 26; k++) {
        if(i + j + k + 3 == n) {
          string s = "";
          s += (char)(i + 'a');
          s += (char)(j + 'a');
          s += (char)(k + 'a');
          cout << s << endl;
          return;
        }
      }
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

