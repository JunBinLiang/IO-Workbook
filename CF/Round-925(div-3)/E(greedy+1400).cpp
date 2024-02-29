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

//7:30 - 7:41
void solve() {
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }

  vector<pair<int, int>> b;
  ll sum = 0;
  for(int i = 0; i < n; i++) {
    int x = a[i];
    string s = to_string(x);
    pair<int, int> p = {0, (int)(s.size())};
    while(x % 10 == 0) {
      x /= 10;
      p.first++;
      p.second--;
    }
    b.push_back(p);
    sum += p.second;
  }

  sort(b.begin(), b.end());
  reverse(b.begin(), b.end());

  for(int i = 1; i < b.size(); i += 2) {
    sum += b[i].first;
  }

  if(sum >= m + 1) {
    cout << "Sasha" << endl;
  } else {
    cout << "Anna" << endl;
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

