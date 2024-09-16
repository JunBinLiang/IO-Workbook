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

const int N = 1e5 + 10;
int p[N], ans[N];

void init() {
    memset(p, 0, sizeof p);
}

int get(int l, int r) {
    return l == 0 ? p[r] : p[r] - p[l - 1];
}

void solve() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        p[a[i]]++;
    }
    
    for(int i = 1; i <= n; i++) {
        p[i] += p[i - 1];
    }

    int leftcount = 0;
    if(n % 2 == 1) leftcount = (n + 1) / 2;
    else leftcount = (n + 2) / 2;

    for(int i = 1; i <= n; i++) {
        int l = 0, r = i - 1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            int s = 0;
            for(int j = i; j <= n; j += i) {
                s += get(j - i, j - i + mid);
                if(j + i > n) { //loop will break
                    if(j <= n) {
                        s += get(j, min(n, j + mid));
                    } 
                }
            }
            
            if(s >= leftcount) {
                ans[i] = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
    }

    for(int i = 0; i < m; i++){ 
        int x;
        scanf("%d", &x);
        printf("%d ", ans[x]);
    }
    printf("\n");
    
    //reset
    for(int i = 0; i <= n; i++) {
        p[i] = 0;
    }
}     

int main() {
    int t = 1;
    std :: cin >> t;
    init();
    while(t--) {
        solve();
    }
    return 0;
}
