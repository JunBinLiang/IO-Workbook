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
const int N = 5e4+ 100;
int sa[N], x[N], y[N], c[N], rk[N], height[N];
char s[N];


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

void solve() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    m = 256;
    
    Sa();
    Height();

    
    int ans = (n - sa[1]) + 1;
    for(int i = 2; i <= n; i++) {
      int curLen = (n - sa[i]) + 1;
      curLen -= height[i];
      ans += curLen;
    }
    
    printf("%d\n", ans);
    
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
