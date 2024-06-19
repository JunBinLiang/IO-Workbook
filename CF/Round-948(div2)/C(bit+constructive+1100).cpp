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
  int n;
  cin >> n;
  vector<int> ans(31);
  for(int i = 0; i < 31; i++) {
    if(n & (1 << i)) ans[i] = 1;
  }

  for(int i = 0; i < 31; i++) {
    if(ans[i]) {
      int j = i;
      while(j < 31 && ans[j]) {
        j++;
      }
      if(j - i > 1) {
        ans[i] = -1;
        ans[j] = 1;
        for(int k = i + 1; k < j; k++) ans[k] = 0;
      }
      i = j - 1;
      
    }
  }

  printf("%d\n", (int)(ans.size()));
  for(int i = 0; i < ans.size(); i++) {
    printf("%d ", ans[i]);
  }
  printf("\n");
  
}

//-111

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
