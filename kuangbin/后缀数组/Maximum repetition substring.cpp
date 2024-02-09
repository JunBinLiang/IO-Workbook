#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <list>
#include<fstream>
#include <bitset>

using namespace std;  

int n, m;
const int N = 1e5 + 100;
int sa[N], x[N], y[N], c[N], rk[N], height[N];
char s[N];

int f[20][N];
int Log[N];

int T = 0;
bool done = false;

//sa[i] : 排名第i 是第几个后缀
//rank[i] : 第i个后缀排名第几
void Sa() {
  for(int i = 0; i <= 256; i++) c[i] = 0;
  for(int i = 0; i <= max(n, m); i++) x[i] = 0;
  for(int i = 0; i <= max(n, m); i++) y[i] = 0;
  //类似第一关键字排序，用前缀和看有多少个小于
  for (int i = 1; i <= n; i ++ ) c[x[i] = s[i]] ++ ;
  for (int i = 2; i <= m; i ++ ) c[i] += c[i - 1];
  for (int i = n; i; i -- ) sa[c[x[i]] -- ] = i;

  for (int k = 1; k <= n; k <<= 1) {
    int num = 0;
    for (int i = n - k + 1; i <= n; i++ ) y[++num] = i;
    for (int i = 1; i <= n; i ++ )
            if (sa[i] > k)
                y[ ++ num] = sa[i] - k; //第二关键字排序
    
    //第一关键字排序
    for (int i = 1; i <= m; i ++ ) c[i] = 0;
    for (int i = 1; i <= n; i ++ ) c[x[i]] ++ ;
    for (int i = 2; i <= m; i ++ ) c[i] += c[i - 1];
    for (int i = n; i; i -- ) sa[c[x[y[i]]] -- ] = y[i], y[i] = 0; //按第二关键字顺序从后往前
    swap(x, y);
    
    //离散化
    x[sa[1]] = 1, num = 1;
    for (int i = 2; i <= n; i ++ )
        x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? num : ++ num;
    if (num == n) break;
    m = num;  
  }
}

//lcp(i, j) = min(lcp(i, k), lcp(k, j))
//height[i] = lcp(i - 1, i)
//h[i] = height(rk[i])
//h[i] >= h[i - 1] - 1
void Height() {
  for (int i = 1; i <= n; i ++ ) rk[sa[i]] = i;
  for (int i = 1, k = 0; i <= n; i ++ ) {
    if (rk[i] == 1) continue;
    if (k) k -- ;
    int j = sa[rk[i] - 1];
    while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k ++ ;
    height[rk[i]] = k;
  }
}

void RMQInit() {
  for(int i = 0; i <= n; i++) {
    f[0][i] = height[i];
  }
  
  int x = 1, cnt = 1;
  for(int i = 1; i <= n; i++) {
      while(i > x) x *= 2, cnt++;
      Log[i] = cnt - 1;
  }

  for(int i = 1; i < 20; i++) {
    for(int j = 0; j <= n; j++) {
      if(j + (1 << (i - 1)) <= n) {
        f[i][j] = min(f[i - 1][j + (1 << (i - 1))], f[i - 1][j]);
      }
    }
  }
}

int lcp(int l, int r) {
  l = rk[l], r = rk[r];
  if(l > r) swap(l, r);
  l++;
  int sz = r - l + 1;
  return min(f[Log[sz]][l], f[Log[sz]][r - (1 << Log[sz]) + 1]);
}

void solve() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    m = 256;
    
    if(s[1] == '#') {
      done = true;
      return;
    }

    T++;
    Sa();
    Height();
    RMQInit();
    
    int mx = -1;
    vector<int> v;
    for(int l = 1; l < n; l++) {
      for(int i = 1; i + l <= n; i += l) {
        int common = lcp(i, i + l);
        int count = common / l + 1;
        int p = i - (l - common % l);
        if(p >= 1 && lcp(p, p + l) >= l) count++;
        if(count > mx) {
          mx = count;
          v.clear();
          v.push_back(l);
        } else if(count == mx) {
          v.push_back(l);
        }
      }
    }

    /*for(int i = 1; i <= n; i++) cout << sa[i] << " ";
    cout << endl;
    for(int x : v) cout << x << " ";
    cout << endl;*/
    if(mx == 1) {
        printf("Case %d: ", T);
        printf("%c", s[sa[1]]);
        printf("\n");
        return;
    }

    int le = -1, p = -1;
    bool flag = false;
    for(int i = 1; i <= n && !flag; i++) {
      for(int j = 0; j < v.size(); j++) {
        int l = v[j];
        if(sa[i] + l <= n && lcp(sa[i], sa[i] + l) >= (mx - 1) * l) {
          p = sa[i];
          le = l * mx;
          flag = true;
          break;
        }
      }
    }
    printf("Case %d: ", T);
    for(int i = p; i < p + le; i++) {
      printf("%c", s[i]);
    }
    printf("\n");
}

int main()
{
    int t = 1;
    //cin >> t;
    while(!done) {
        solve();
    }
    return 0;
}
