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
const int N =  1e6 + 10;
int p[N * 2];
vector<int> pri[N], pos[N];
bool isp[N];
void init() {
  memset(isp, 0, sizeof isp);
  for(int i = 2; i < N; i++) {
    if(isp[i]) continue;
    for(int j = i; j < N; j += i) {
      isp[j] = true;
      pri[j].push_back(i);
    }
  }
}

int find(int u) {
  return p[u] == u ? u : p[u] = find(p[u]);
}

void merge(int r1, int r2) {
  if(r1 != r2) {
    p[r1] = r2;
  }
}

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  vector<int> a(n);
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }

  for(int i = 0; i < n; i++) {
    a.push_back(a[i]);
  }
  
  //each number is seperate as upper half and lower half except the first one
  for(int i = 0; i <= 2 * n; i++) p[i] = i;
  long long add = 0;
  if(a[0] != 1) {
    merge(find(0), find(n));
  } else {
    add += n;
  }

  if(k >= n) {
    for(int i = 1; i < n; i++) {
      if(a[i] != 1)
        merge(find(i), find(i + n));
    }
  }
  
  for(int i = 1; i < n; i++) {
    if(a[i] == 1) add += n;
  }

  //each number has at most 10 distinct primes 
  unordered_set<int> distinctPrimes;
  for(int i = 0; i < a.size(); i++) {
    for(int pr : pri[a[i]]) {
      pos[pr].push_back(i);
      distinctPrimes.insert(pr);
    }
  }
  
  for(auto pr : distinctPrimes) {
    for(int i = 1; i < pos[pr].size(); i++) {
      if(pos[pr][i] - pos[pr][i - 1] <= k) { //within distance
        if(pos[pr][i - 1] == 0) continue;
        merge(find(pos[pr][i - 1]), find(pos[pr][i]));
        //cout << "merge " << pos[pr][i - 1] << " " << pos[pr][i] << endl;
      }
    }
  }

  //reset
  for(int i = 0; i < a.size(); i++) {
    for(int pr : pri[a[i]]) {
      pos[pr].clear();
    }
  }

  set<int> s;
  for(int i = 0; i < 2 * n; i++) {
    if(a[i] == 1) continue;
    s.insert(find(i));
  }
  printf("%lld\n", (long long)(s.size() + add));
}

/*
1 2 3 4 5 6    1 2 3 4 5 6
6 1 2 3 4 5
5 6 1 2 3 4
4 5 6 1 2 3
3 4 5 6 1 2
2 3 4 5 6 1
*/

/*
2 1 2 1 1
1 2 1 2 1
1 1 2 1 2
2 1 1 2 1
1 2 1 1 2
*/

int main(){
  init();
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
