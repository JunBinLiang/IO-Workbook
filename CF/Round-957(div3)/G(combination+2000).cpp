#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include <string.h>

using namespace std;
using ll = long long;

const int N = 5010;
const int MOD = 1e9 + 7;
long long fact[N * 2 + 100];

ll fpow(ll x, int y){
	ll res = 1;
	while(y){
		if(y & 1) res = (res * x) % MOD;
		x = (x * x) % MOD;
		y >>= 1;
	}
	return res;
}  

ll C(int n, int m) {
  return fact[n] * fpow(fact[n - m], MOD - 2) % MOD * fpow(fact[m], MOD - 2) % MOD;
}

long long c[5006][5006];
void init() {
    c[0][0] = 1;
    for(int i = 1;i <= 5005; i++) {
      c[i][0]=1;
      for(int j = 1;j <= i;j++) {
        c[i][j] = ( c[i-1][j] + c[i-1][j-1] ) % MOD;
      }
    }
}

void solve() {
    int n;
    scanf("%d", &n);
    
    fact[0] = 1;
    for(int i = 1; i <= (2 * n + 1); i++) {
        fact[i] = fact[i - 1] * i;
        fact[i] %= MOD;
    }

    long long ans = 1;
    for(int i = 1; i <= n; i++) { //sz
        int empty = i + 1;
        for(int k = empty; k <= 2 * (n + 1); k++) { //MEX
            //The ith MEX is k, how many such subset
            if(k <= n) {
                int left = k - empty;
                int right = i - left;
                if(right >= 0 && right <= n - k) {
                    long long ways = c[n - k][right] * c[k - 1][left];
                    ways %= MOD;
                    ans += ways * k;
                }
            } else {
                if(i + empty == k) {
                    ans += C(n, i) * k;
                }
            }
            ans %= MOD;
        }
    }
    cout << ans << endl;
}    

int main() {
    int t = 1;
    cin >> t;
    init();
    while(t--) {
        solve();
    }
    return 0;
}
