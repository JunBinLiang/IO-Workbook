#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<unordered_set>
#include<string>
#include <string.h>

using namespace std;
using ll = long long;

const int MOD = 998244353;
const int N = 2e5 + 10;
long long fact[N];
void init() {
    fact[0] = 1;
    for(int i = 1; i < N; i++) {
        fact[i] = fact[i - 1] * i;
        fact[i] %= MOD;
    }
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

void solve() {
    int n;
    std :: cin >> n;
    std :: vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) std :: cin >> a[i];

    if(a[n] != n && a[n] != -1) {
        std :: cout << 0 << std :: endl;
        return;
    }

    for(int i = 1; i <= n; i++) {
        if(a[i] != -1 && a[i] > i) {
            std :: cout << 0 << std :: endl;
            return;
        }
    }

    std :: vector<int> pos;
    for(int i = 1; i <= n; i++) {
        if(a[i] != -1) {
            pos.push_back(i);
        }
    }

    if(pos.size() == 0) {
        std :: cout << fact[n] << std :: endl;
        return;
    }
    
    long long ans = 1;
    int notfill = 0;
    for(int i = 0; i < pos.size(); i++) {
        if(i == 0) {
            notfill += pos[i];
            ans *= (C(notfill, a[pos[i]]) * fact[a[pos[i]]]);
            ans %= MOD;
            notfill -= a[pos[i]];
        } else {
            int newadd = pos[i] - pos[i - 1];
            int mustfill = a[pos[i]] - a[pos[i - 1]];
            long long ways = 0;
            for(int l = 0; l <= notfill; l++) {
                int r = mustfill - l;
                if(l > newadd || r < 0) break;
                if(r > newadd) continue;
                long long fillleft = (C(notfill, l) * C(newadd, l) % MOD) * fact[l];
                fillleft %= MOD;
                long long fillright = (C(newadd, r) * C(notfill + newadd - l, r) % MOD) * fact[r];
                fillright %= MOD;
                ways += (fillleft * fillright);
                ways %= MOD;
            }
            ans *= ways;
            ans %= MOD;
            notfill += newadd - mustfill;
        }
        //cout << i << " " << ans <<"  " << notfill << endl;
    }

    if(pos.back() != n) {
        long long ways = C(n - pos.back(), notfill) * fact[notfill];
        ways %= MOD;
        ways *= fact[n - pos.back()];
        ways %= MOD;
        ans *= ways;
        ans %= MOD;
    } else {
        ans *= fact[notfill];
        ans %= MOD;
    }
    ans %= MOD;
    std :: cout << ans << std :: endl;
}    

int main() {
    int t = 1;
    init();
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
