#include<iostream>
#include<algorithm>
#include<vector>
#include<unordered_set>
#include<set>
#include<unordered_map>
#include<map>
#include<string>
#include <string.h>
#include <bitset>
#include <queue>
#include <cmath>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ll = long long;

template<class TIn, class TOut = null_type>
using order_tree = tree<TIn, TOut, less<TIn>, rb_tree_tag,
	tree_order_statistics_node_update>;

const int N = 4e5 + 100;
const int MOD = 998244353;

long long fact[N];

ll modInverse(ll a, ll m) {
    ll m0 = m;
    ll y = 0, x = 1;
    if (m == 1)
        return 0;
    while (a > 1) {
        // q is quotient
        ll q = a / m;
        ll t = m;
        // m is remainder now, process
        // same as Euclid's algo
        m = a % m;
        a = t;
        t = y;
        // Update x and y
        y = x - q * y;
        x = t;
    }
    // Make x positive
    if (x < 0)
        x += m0;
    return x;
}

ll fpow(ll x, int y){
	ll res = 1;
	while(y){
		if(y & 1) res = (res * x) % MOD;
		x = (x * x) % MOD;
		y >>= 1;
	}
	return res;
}  

ll C(int n,int m) {
  return fact[n] * fpow(fact[n - m], MOD - 2) % MOD * fpow(fact[m], MOD - 2) % MOD;
}

const int SIZE = 200000 + 100;
struct Fenwick {
  int tree[SIZE];
  void init(int n) {
    for(int i = 0; i <= n + 1; i++) tree[i] = 0;
  }

  void update(int i, int val) {
    i++;
    while(i < SIZE){
      tree[i] += val;
      i += (i & -i);
    }
  }

  int pre(int i) {
    int sum = 0;
    while(i>0){
      sum += tree[i];
      i -= ( i & -i);
    }
    return sum;
  }
  int query(int i, int j) {
      return pre(j + 1) - pre(i);
  }
} tr;

int findk(int n, int k) {
    int l = 1, r = n;
    int ans = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(tr.query(0, mid) >= k) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

void init() {
    fact[0] = 1;
    for(int i = 1; i < N; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    tr.init(200000 + 10);
    for(int i = 1; i < 200000 + 10; i++) tr.update(i, 1);
}

void solve() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<pair<int, int>> a(m);
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &a[i].first, &a[i].second);
    }

    int cutpoint = 0;
    int j = m - 1;
    vector<int> del;
    while(j >= 0) {
        int l = a[j].second, r = a[j].first;
        int kth = findk(n, l);
        int kthNxt = findk(n, l + 1);
        if(kth + 1 == kthNxt) {
            cutpoint++;
        }
        tr.update(kth, -1);
        del.push_back(kth);
        j--;
    }
    for(int kth : del) tr.update(kth, 1);
    int ans = C(n * 2 - cutpoint - 1, n);
    printf("%d\n", ans);
}     

int main() {
    int t = 1;
    init();
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
