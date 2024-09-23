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

using namespace std;
const int N = 2e7 + 10;
bool isp[N];
vector<int> pri;
void init() {
    memset(isp, 0, sizeof isp);
    pri.push_back(1);
    for(int i = 2; i < N; i++) {
        if(isp[i]) continue;
        pri.push_back(i);
        for(int j = i; j < N; j += i) {
            isp[j] = true;
        }
    }
    /*cout << pri.size() << endl;
    int dif = 0;
    for(int i = 1; i < pri.size(); i++) dif = max(dif, pri[i] - pri[i - 1]);
    cout << dif << endl;*/
}

bool add = false;
long long dp[400][400];
int lastp = -1;
int n, m, x, y;

long long dfs(int i, int j) {
    if(dp[i][j] != -1) {
        return dp[i][j];
    }
    int v1 = 0, v2 = 0;
    if(add) {
        v1 = i + pri[lastp - 1];
        v2 = j + pri[lastp - 1];
    } else {
        v1 = i;
        v2 = j;
    }
    long long ans = (v1 + 0ll) * x + (v2 + 0ll) * y;
    
    if(v1 + 1 <= n && __gcd(v1 + 1, v2) == 1) {
        ans = max(ans, dfs(i + 1, j));
    }
    if(v2 + 1 <= n && __gcd(v1, v2 + 1) == 1) {
        ans = max(ans, dfs(i, j + 1));
    }
    return dp[i][j] = ans;
}

void solve() {
    scanf("%d%d%d%d", &n, &m, &x, &y);
    memset(dp, -1, sizeof dp);
    int l = 0, r = pri.size() - 1;
    lastp = 0;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(pri[mid] <= n) {
            lastp = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }   
    
    if(n >= 400) add = true;
    else add = false;
    
    long long ans = 0;
    if(!add) {
        ans = max(dfs(0, 1), dfs(1, 0));
    } else {
        ans = max(dfs(0, pri[lastp] - pri[lastp - 1]), dfs(pri[lastp] - pri[lastp - 1], 0));
    }
    printf("%lld\n", ans);
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
