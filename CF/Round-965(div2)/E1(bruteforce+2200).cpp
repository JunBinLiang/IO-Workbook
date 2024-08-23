#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<unordered_set>
#include<map>
#include<string>
#include <string.h>
#include <bitset>
#include <queue>

using namespace std;

const int N = 2e5 + 10;
long long p[N];
int a[N];
long long get(int l, int r) {
    return l == 0 ? p[r] : p[r] - p[l - 1];
}

int toright(long long val, int i, int n) {
    int po = -1;
    int l = i + 1, r = n - 1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(get(i + 1, mid) <= val) {
            po = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return po;
}

int toleft(long long val, int i, int n) {
    int l = 0, r = i - 1;
    int po = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(get(mid, i - 1) <= val) {
            po = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    return po;
}

void solve() {
    int n, m, ans = 0;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for(int i = 0; i < n; i++) {
        p[i] = a[i];
        if(i) p[i] += p[i - 1];
    }


    for(int i = 0; i < n; i++) {
        long long cur = a[i];
        int l = i, r = i;
        while(true) {
            int j = toright(cur, r, n);
            int k = toleft(cur, l, n);
            if(j == -1 && k == -1) break;
            if(j != -1) r = j;
            if(k != -1) l = k;
            cur = get(l, r);
        }

        if(cur == p[n - 1]) {
            ans++;
        }
    }

    printf("%d\n", ans);
}    

int main() {
    int t = 1;
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
