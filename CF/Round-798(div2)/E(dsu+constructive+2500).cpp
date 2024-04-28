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

const int N = 2010;
int p[N], cnt[N], f[N];

int find(int u) {
  return p[u] == u ? u : p[u] = find(p[u]);
}

int find1(vector<int>& nums, int u) {
  return nums[u] == u ? u : nums[u] = find1(nums, nums[u]);
}

vector<int> pos[31];


void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }
  vector<int> b(a.begin(), a.end());

  memset(cnt, 0, sizeof cnt);
  for(int i = 0; i < n; i++) p[i] = i;
  for(int i = 0; i < n; i++) {
    if(a[i] == 0) a[i]++;
  }

  for(int i = 0; i < n; i++) {
    for(int j = i + 1; j < n; j++) {
      if((a[i] & a[j]) > 0) {
        int r1 = find(i), r2 = find(j);
        if(r1 != r2) p[r1] = r2;
      }
    }
  }

  set<int> roots;
  for(int i = 0; i < n; i++) {
    int r = find(i);
    roots.insert(r);
    cnt[r]++;
    //cout << r << " ";
  }
  //cout << endl;
  if(roots.size() == 1) {
      int s = 0;
      for(int i = 0; i < b.size(); i++) {
        s += abs(a[i] - b[i]);
      }
      printf("%d\n", s);
      for(int x : a) printf("%d ", x);
      printf("\n");
      return;
  }
  

  bool oneStep = false;
  for(int i = 0; i < n; i++) {
    if(a[i] == 1) continue;
    for(int j = 0; j < 31; j++) pos[j].clear();
    a[i]--;
    for(int j = 0; j < n; j++) {
      for(int k = 0; k < 31; k++) {
        if(a[j] & (1 << k)) {
          pos[k].push_back(j);
        }
      }
    }

    vector<int> nums(n);
    for(int j = 0; j < n; j++) nums[j] = j;
    for(int j = 0; j < 31; j++) {
      auto& v = pos[j];
      for(int k = 1; k < v.size(); k++) {
        int r1 = find1(nums, v[k]);
        int r2 = find1(nums, v[k - 1]);
        if(r1 != r2) nums[r1] = r2;
      }
    }

    set<int> se;
    for(int j = 0; j < n; j++) se.insert(find1(nums, j));
    if(se.size() == 1) {
      oneStep = true;
      break;
    }
    a[i]++;
  }
  
  int hasone = -1; 
  for(int i = 0; i < n; i++) {
      if(a[i] % 2 == 1) hasone = find(i);
  }
  
  if(roots.size() > 1 && !oneStep) {
    if(roots.size() == 2 && hasone != -1) {
        for(int i = 0; i < n; i++) {
            int r1 = find(i);
            if(r1 != hasone) {
                a[i]++;
                break;
            }
        }
    } else {
      int maxFirst = -1;
      int r = -1, index = -1;
      for(int i = 0; i < n; i++) {
        int r1 = find(i);
        int first = -1;
        for(int j = 0; j < 31; j++) {
          if(a[i] & (1 << j)) {
            first = j;
            break;
          }
        }
        f[i] = first;
        if(first > maxFirst) {
          maxFirst = first;
          r = r1;
          index = i;
        }
      }
      //cout << "index " << index <<" " << r << " " << cnt[r] << endl;
      if(cnt[r] == 1) {
        a[index]--;
      } else {
        bool ok = true;
        a[index]--;
        int bad = -1;
        
        for(int i = 0; i < n; i++) {
            int r1 = find(i);
            if(r1 == r) {
                bool check = false;
                for(int j = 0; j < n; j++) {
                    if(i == j) continue;
                    int r2 = find(j);
                    if(r2 == r) {
                        if(a[i] & a[j]) {
                            check = true;
                        }
                    }
                }
                if(!check) {
                    bad = i;
                }
            }
        }
        
        if(bad != -1) {
          if(bad == index) {
              for(int i = 0; i < n; i++) {
                  int r1 = find(i);
                  if(r1 == r && i != index) {
                      a[i]++;
                      break;
                  }
              }
          }
          else a[bad]++;
        }
      }    
    }
  }

  int s = 0;
  for(int i = 0; i < b.size(); i++) {
    s += abs(a[i] - b[i]);
  }
  printf("%d\n", s);
  for(int x : a) printf("%d ", x);
  printf("\n");
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}

//1000100000
//0011100000
//1000010000
