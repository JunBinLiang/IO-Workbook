#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include <string.h>

using namespace std;

const int N = 1e5 + 10;
int tr[N * 32][2], cnt[N * 32 * 2];
int a[N];
int n, idx = 1;
long long k;

void init() {
    memset(tr, -1, sizeof tr);
    memset(cnt, 0, sizeof cnt);
    idx = 1;
}

void add(int n) {
    int u = 0;
    for(int i = 30; i >= 0; i--) {
        int b = 0;
        if(n & (1 << i)) b = 1;
        if(tr[u][b] == -1) {
            tr[u][b] = idx++;
        }
        u = tr[u][b];
        cnt[u]++;
    }
}

void del(int n) {
    int u = 0;
    for(int i = 30; i >= 0; i--) {
        int b = 0;
        if(n & (1 << i)) b = 1;
        u = tr[u][b];
        cnt[u]--;
    }
}

int find(int n) {
    int u = 0, ans = 0;
    for(int i = 30; i >= 0; i--) {
        int b = 0;
        if(n & (1 << i)) b = 1;
        if(tr[u][b] != -1 && cnt[tr[u][b]] > 0) u = tr[u][b];
        else {
            ans += (1 << i);
            u = tr[u][b ^ 1];
        }
    }
    return ans;
}

long long check(int mid) {
    long long ans = 0;
    add(a[0]);
    for(int i = 1, j = 0; i < n; i++) {
        int minv = find(a[i]);
        if(minv <= mid) {
            while(j < i) {
                int mn = find(a[i]);
                if(mn <= mid) {
                    ans += (n - i);
                    del(a[j]);
                    j++;
                }
                else {
                    break;
                }
            }
        }
        add(a[i]);
    }

    //clear
    for(int i = 0; i <= idx + 1; i++) {
        tr[i][0] = tr[i][1] = -1;
        cnt[i] = 0;
    }
    idx = 1;
    return ans;
}


void solve() {
    scanf("%d%lld", &n, &k);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int l = 0, r = 2e9;
    int ans = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        long long count = check(mid);
        if(count >= k) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    printf("%d\n", ans);
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
