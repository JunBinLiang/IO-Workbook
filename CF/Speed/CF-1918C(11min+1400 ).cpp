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


//9:49 - 10:00
void solve() {

    ll a, b, r;
    cin >> a >> b >> r;

    ll x = 0, o = 0;
    vector<pair<int, int>> c;
    int j = -1;
    for(int i = 63; i >= 0; i--) {
      int b1 = 0, b2 = 0;
      if(a & (1ll << i)) b1 = 1;
      if(b & (1ll << i)) b2 = 1;
      if(b1 == b2) continue;
      j = i;
      o += (1ll << i);
      if(b1 == 1) {
      
      } else {
        swap(a, b); //a is greater than b
      }
      break;
    }

    for(int i = j - 1; i >= 0; i--) {
      int b1 = 0, b2 = 0;
      if(a & (1ll << i)) b1 = 1;
      if(b & (1ll << i)) b2 = 1;
      if(b1 == b2) continue;
      if(b1 == 1 && x + (1ll << i) <= r) {
        x += (1ll << i);
      }
    }

    cout << abs((a ^ x) - (b ^ x)) << endl;
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
