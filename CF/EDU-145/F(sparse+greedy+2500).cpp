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


const int N = 4e5 + 100;
int f[N][20];
ll c[N][20]; //cost

ll get(vector<ll>& p, int l, int r) {
  return l == 0 ? p[r] : p[r] - p[l - 1];
}

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  vector<int> a(n), b(n);
  for(int i = 0; i < n; i++) scanf("%d", &a[i]);
  for(int i = 0; i < n; i++) scanf("%d", &b[i]);
  for(int i = 0; i < n; i++) a.push_back(a[i]);
  for(int i = 0; i < n; i++) b.push_back(b[i]);


  vector<ll> p(n * 2);
  for(int i = 0; i < n * 2; i++) {
    p[i] = a[i];
    if(i) p[i] += p[i - 1]; 
  }

  vector<int> nxtone(2 * n, -1);
  int one = -1;
  for(int i = 2 * n - 1; i >= 0; i--) {
    if(b[i] == 1) {
      nxtone[i] = one;
      one = i;
    }
  }

  //reset
  for(int i = 0; i <= n * 2 + 1; i++) {
    for(int j = 0; j < 20; j++) {
      f[i][j] = c[i][j] = -1;
    }
  }

  //1: take the full power
  //2: take enough power until next one
  for(int i = 0; i < n * 2; i++) {
    if(b[i] == 1) {
      if(nxtone[i] != -1) {
        ll dis = get(p, i, nxtone[i] - 1);
        if(k >= dis) {
          f[i][0] = nxtone[i];
          c[i][0] = dis;
          continue;
        }
      } 

      int l = i, r = n * 2 - 1;
      int po = -1;
      while(l <= r) {
        int mid = l + (r - l) / 2;
        ll need = get(p, i, mid);
        if(k <= need) {
          po = mid;
          r = mid - 1;
        } else {
          l = mid + 1;
        }
      }
      
      if(po == -1) {
        f[i][0] = 2 * n;
        c[i][0] = get(p, i, 2 * n - 1);
      } else {
        ll need = get(p, i, po);
        f[i][0] = po + 1;
        c[i][0] = k + (need - k) * b[po];   
      }
    } else {
      f[i][0] = i + 1;
      c[i][0] = a[i] * 2;
    }
  }
  
  
  //for(int i = 0; i < 2 * n; i++) cout << f[i][0] << " ";
  //cout << endl << endl;
  //for(int i = 0; i < 2 * n; i++) cout << c[i][0] << " ";
  //cout << endl << endl;
  

  for(int j = 1; j < 20; j++) {
    for(int i = 0; i < 2 * n; i++) {
      if(f[i][j - 1] != -1) {
        f[i][j] = f[f[i][j - 1]][j - 1];
        c[i][j] = c[i][j - 1] + c[f[i][j - 1]][j - 1];
      }
    }
  }
  
  //cout << f[1][0] << "  " << f[1][1] << "  " << endl;
  //cout << c[1][0] << "  " << c[1][1] << "  " << endl;
  //cout << c[0][3] << endl;
  //cout << endl;
  
  for(int i = 0; i < n; i++) { //answer
    ll s = 0;
    int l = i, r = i + n;
    for(int j = 19; j >= 0; j--) {
      if(f[l][j] == -1) continue;
      if(f[l][j] <= r) {
        //cout << l << "  " << j << "   |" << f[l][j] <<"  " << c[l][j] << endl;
        s += c[l][j];
        l = f[l][j];
      }
    }
    if(l != r) {
      ll step = get(p, l, r - 1);
      s += step * b[l]; 
    }
    printf("%lld ", s);
  }
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
