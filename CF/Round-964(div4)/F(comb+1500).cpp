#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<unordered_set>
#include<string>
#include <string.h>
#include <bitset>
#include <queue>

using namespace std;

const int MOD = 1e9 + 7;
const int N = 2e5 + 10;
long long fact[N];

long long fpow(long long x, int y){
	long long res = 1;
	while(y){
		if(y & 1) res = (res * x) % MOD;
		x = (x * x) % MOD;
		y >>= 1;
	}
	return res;
}  
  

long long C(int n,int m) {
  return fact[n] * fpow(fact[n - m], MOD - 2) % MOD * fpow(fact[m], MOD - 2) % MOD;
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    vector<int> cnt(2);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }

    fact[0] = 1;
    for(int i = 1; i <= n; i++) {
        fact[i] = fact[i - 1] * i;
        fact[i] %= MOD;
    }

    //Median must be 1
    long long ans = 0;
    int righthalf = k / 2 + 1;
    if(cnt[1] >= righthalf) {
        for(int i = righthalf; i <= min(k, cnt[1]); i++) {
            int one = i, zero = k - i;
            if(cnt[0] >= zero) {
                long long ways = C(cnt[1], cnt[1] - one) * C(cnt[0], zero);
                ways %= MOD;
                ans += ways;
                ans %= MOD;
            }
        }
    }

    cout << ans << endl;
}    

int main() {
    int t = 1;
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
