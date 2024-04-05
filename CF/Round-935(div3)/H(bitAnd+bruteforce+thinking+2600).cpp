#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

int getAnd(vector<int>& count, int n) {
  int ans = 0;
  for(int i = 0; i < count.size(); i++) {
    if(count[i] == n) ans += (1 << i);
  }
  return ans;
}

void del(vector<int>& count, int x) {
  for(int i = 0; i < 25; i++) {
    if(x & (1 << i)) count[i]--;
  }
}

void add(vector<int>& count, int x) {
  for(int i = 0; i < 25; i++) {
    if(x & (1 << i)) count[i]++;
  }
}

void solve() {
  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  } 
  sort(a.begin(), a.end());

  vector<int> count(25);
  for(int x : a) {
    for(int i = 0; i < 25; i++) {
      if(x & (1 << i)) {
        count[i]++;
      }
    }
  }

  vector<vector<int>> p(a.back() + 1);
  for(int i = 0; i < n; i++) {
    for(int j = 1; j * j <= a[i]; j++) {
      if(a[i] % j == 0) {
        int g1 = j, g2 = a[i] / j;
        p[g1].push_back(a[i]);
        if(g1 != g2) {
          p[g2].push_back(a[i]);
        }
      }
    }
  }

  int x = -1, y = -1;
  for(int g = 1; g < p.size() && x == -1; g++) {
    if(p[g].size() < 2) continue;
    vector<int>& v = p[g];
    vector<int> t(25, -1);
    for(int i = 0; i < v.size(); i++) {
      if(i) {
        del(count, v[i]);
        unordered_set<int> s;
        for(int j = 24; j >= 0; j--) {
          if(count[j] == n - 2) {
            if(t[j] != -1) {
              s.insert(t[j]);
              if(s.size() == i) { //full
                del(count, v[t[j]]);
                if(getAnd(count, n - 2) + k < g) {
                  x = v[i];
                  y = v[t[j]];
                  //cout << "ok " << g <<" " << getAnd(count, n - 2) << endl;
                  //cout << v <<" " << count << endl;
                }
                add(count, v[t[j]]);
                break;
              }
            }
          }
        }
        
        if(s.size() < i) {
          for(int j = 0; j < i; j++) {
            if(s.find(j) == s.end()) {
              if(getAnd(count, n - 1) + k < g) {
                x = v[i];
                y = v[j];
              }
              break;
            }
          }
        }
        add(count, v[i]);
      }

      for(int j = 0; j < 25; j++) {
        if((v[i] & (1 << j)) == 0) {
          t[j] = i;
        }
      }
    }
  }

  if(x != -1) {
    printf("YES\n");
    printf("2 %d %d\n", x, y);
    printf("%d ", n - 2);
    for(int i = 0; i < n; i++) {
      if(a[i] == x) {
        x = -1;
        continue;
      }
      if(a[i] == y) {
        y = -1;
        continue;
      }
      printf("%d ", a[i]);
    }
    printf("\n");
    return;
  }

  printf("NO\n");

}


int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}

