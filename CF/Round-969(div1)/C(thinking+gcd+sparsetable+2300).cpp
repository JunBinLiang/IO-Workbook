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

const int N = 4e5 + 10;
int st[N][20];

void init(vector<int>& a) {
    int n = a.size();
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j < 20; j++) {
            st[i][j] = -1;
        }
    }

    for(int i = 0; i < n; i++) {
        st[i][0] = a[i];
    }

    for(int j = 1; j < 20; j++) {
        for(int i = 0; i < n; i++) {
            if((i + (1 << j)) - 1 < n) {
                st[i][j] = __gcd(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
}

int query(int l, int r) {
    int g = -1;
    for(int i = 19; i >= 0; i--) {
        if((l + (1 << i)) - 1 <= r) {
            if(g == -1) g = st[l][i];
            else g = __gcd(g, st[l][i]);
            l += (1 << i);
        }
    }
    return g;
}   

void solve() {
    int n; long long ans = 0;
    scanf("%d", &n);
    ans = n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    vector<int> b;
    for(int i = 1; i < n; i++) {
        int v = (abs(a[i] - a[i - 1]));
        while(v % 2 == 0 && v > 0) v /= 2;
        b.push_back(v);
    }
    
    for(int i = 0; i < b.size(); i++) {
        if(b[i] != 0) continue;
        int j = i;
        int cnt = 0;
        while(j < b.size() && b[j] == b[i]) {
            j++;
            cnt++;
        }
        ans += ((1ll + cnt) * cnt / 2);
        i = j - 1;
    }
    
    init(b);
    
    for(int i = 0, j = 0; i < b.size(); i++) {
        int g = query(j, i);
        if(g == 1) {
            while(query(j, i) == 1) {
                ans += (b.size() - i);
                j++;
            }
        }
    }
    printf("%lld\n", ans);
}     

int main() {
    int t = 1;
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
