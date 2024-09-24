//Pass with 8000ms

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
    for(int i = 2; i < pri.size(); i++) dif = max(dif, pri[i] - pri[i - 2]); 
    cout << dif << endl;  //200 
    */
    
    //There must 3 distinct prime greater than 400 within a range of 200 at most
}


int n, m, x, y;
int p1 = -1, p2 = -1;
int start1 = 0, start2 = 0;
bool dp[410][410];
long long ans = 0;
void dfs1(int i, int j) {
    int v1 = i, v2 = j;
    ans = max(ans, (v1 + 0ll) * x + (v2 + 0ll) * y);
    dp[i][j] = true;
    for(int l = v1; l <= n; l++) {
        for(int r = v2; r <= m; r++) {
            if(__gcd(l, r) == 1) {
                int ii = l, jj = r;
                if((ii > 0 && dp[ii - 1][jj]) || (jj > 0 && dp[ii][jj - 1])) {
                    dp[ii][jj] = true;
                    ans = max(ans, (l + 0ll) * x + (r + 0ll) * y);
                }
            }
        }
    }
}

long long dfs2(int i, int j) {
    int v1 = i + start1, v2 = j + start2;
    ans = max(ans, (v1 + 0ll) * x + (v2 + 0ll) * y);
    dp[i][j] = true;
    for(int l = v1; l <= n; l++) {
        for(int r = v2; r <= m; r++) {
            if(__gcd(l, r) == 1) {
                int ii = l - start1, jj = r - start2;
                if((ii > 0 && dp[ii - 1][jj]) || (jj > 0 && dp[ii][jj - 1])) {
                    dp[ii][jj] = true;
                    ans = max(ans, (l + 0ll) * x + (r + 0ll) * y);
                }
            }
        }
    }
    return ans;
}

int find(int t) {
    int l = 0, r = pri.size() - 1;
    int p = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(pri[mid] <= t) {
            p = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return p;
}
int c = 0;
void solve() {
    scanf("%d%d%d%d", &n, &m, &x, &y);
    //n = 7230478; m = 11521186; x = 110210643; y = 639585840;
    if(n > m) {
        swap(n, m);
        swap(x, y);
    }
    
    ans = 0;
    c++;
    p1 = find(n);
    p2 = find(m);
    if(p1 == p2) p1--;
    
    //cout << endl;
    //cout << n << " " << m << " " << x << " " << y << " " << p1 << " " << p2 << endl;

    if(m <= 400) {
        memset(dp, 0, sizeof dp);
        dfs1(0, 0);
    } else {
        start2 = pri[p2];
        if(n <= 400) {
            start1 = 0;
            memset(dp, 0, sizeof dp);
            ans = max(ans, dfs2(0, 0));
        } else {
            int cnt1 = 0, cnt2 = 0;
            long long t = 1;
            for(int j = p1; j >= 0 && t <= m; j--) {
                t *= pri[j];
                memset(dp, 0, sizeof dp);
                start1 = pri[j];
                ans = max(ans, dfs2(0, 0));
                cnt1++;
            } 
            
            t = 1;
            swap(p1, p2);
            swap(x, y);
            swap(n, m);
            start2 = pri[p2];
            for(int j = p1; j >= 0 && t <= m; j--) {
                t *= pri[j];
                memset(dp, 0, sizeof dp);
                start1 = pri[j];
                ans = max(ans, dfs2(0, 0));
                cnt2++;
            } 
            //cout << cnt1 << " " << cnt2 << endl;
        }
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
