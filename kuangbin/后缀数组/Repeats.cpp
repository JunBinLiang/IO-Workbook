#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <list>
#include<fstream>
#include <bitset>

using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define pb push_back
#define P pair
#define V vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define FFOR(i, a, b) for (int i = a; i <= b; ++i)

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}



int n, m;
const int N = 1e5 + 100;
int sa[N], x[N], y[N], c[N], rk[N], height[N];
char s[N];

int f[20][N];


//sa[i] : 排名第i 是第几个后缀
//rank[i] : 第i个后缀排名第几
void Sa() {
  memset(c, 0, sizeof c);
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
  memset(f, 0, sizeof f);

  for(int i = 0; i <= n; i++) {
    f[0][i] = height[i];
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

  int mn = f[0][l];
  for(int i = 19; i >= 0; i--) {
    if(l + (1 << i) - 1 <= r) {
      mn = min(mn, f[i][l]);
      l += (1 << i);
    }
  }
  return mn;
}

void solve() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
      char c[2];
      scanf("%s", c);
      s[i] = c[0];
    }
    m = 256;
    
    Sa();
    Height();
    RMQInit();
    
    int ans = 0;
    for(int l = 1; l < n; l++) {
      for(int i = 1; i + l <= n; i += l) {
        int common = lcp(i, i + l);
        int count = common / l + 1;
        int p = i - (l - common % l);
        if(p >= 1 && lcp(p, p + l) >= l) count++;
        ans = max(ans, count);
      }
    }
    cout << ans << endl;
}

int main()
{
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
