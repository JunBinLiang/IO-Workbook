//https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P3649

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




const int N = 5e5 + 100;
struct PalindromeTree {
    char s[N];
    int len[N], fail[N], ch[N][26], cnt[N];
    int tot = 0, last = 0;    
    
    void init() {
        memset(cnt, 0, sizeof cnt);
        s[0] = -1;
        len[0] = 0; //初始化even root 
        len[1] = -1;//初始化odd root 
        fail[0] = 1;
        fail[1] = 1;
        tot = 1;
        last = 0;
    }
    
    int getfail(int x, int i) { //寻找fail node
        while(i - len[x] - 1 < 0 || s[i - len[x] - 1] != s[i]) x = fail[x];
        return x;
    }
    
    int newnode(int x) { //简历长度为x 的新node
        tot++;
        len[tot] = x;
        return tot;
    }

    
    void add(int i) {
        s[i] -= 'a';
        int failnode = getfail(last, i);
        if(ch[failnode][s[i]] == 0) { //需要新建node
            int node = newnode(len[failnode] + 2); //前后都加上新字符，所以新回文串长度要加2
            fail[node] = ch[getfail(fail[failnode], i)][s[i]]; //因为fail指向的是原串的严格后缀，所以要从failnode的fail开始找起 
            ch[failnode][s[i]] = node;
        }
        last = ch[failnode][s[i]];
        cnt[last]++;
    }
} pt1;




void solve() {
    scanf("%s", pt1.s + 1);
    int n = strlen(pt1.s + 1);
    
    pt1.init();
    for(int i = 1; i <= n; i++) {
        pt1.add(i);
    }
    
    ll ans = 0;
    for(int i = pt1.tot; i >= 2; i--) {
      ans = max(ans, (pt1.cnt[i] + 0ll) * pt1.len[i]);
      pt1.cnt[pt1.fail[i]] += pt1.cnt[i];
    }

    cout << ans << endl;

}

int main()
{
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
