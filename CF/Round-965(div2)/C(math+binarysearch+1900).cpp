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

int bin(vector<pair<int, int>>& a, long long val) { //bin less
    int p = -1;
    int l = 0, r = a.size() - 1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(a[mid].first < val) {
            p = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return p;
}

int bin1(vector<int>& a, long long val) { //bin less
    int p = -1;
    int l = 0, r = a.size() - 1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(a[mid] < val) {
            p = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return p;
}

const int N = 2e5 + 10;
long long p1[N];

long long get(int l, int r) {
    return l == 0 ? p1[r] : p1[r] - p1[l - 1];
}
//2:16 - 3:15
void solve() {
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> a(n);
    for(int i = 0; i < n; i++) cin >> a[i].first;
    for(int i = 0; i < n; i++) cin >> a[i].second;
    sort(a.begin(), a.end());
    vector<int> b;
    for(int i = 0; i < n; i++) {
        if(a[i].second) {
            b.push_back(i);
        } 
    }

    for(int i = 0; i < b.size(); i++) {
        p1[i] = a[b[i]].first;
        if(i) p1[i] += p1[i - 1];
    }

    long long ans = 0;
    for(int i = 0; i < n; i++) {
        int j = (n - 2) / 2;
        if(j < i) {

        } else {
            j++;
        }
        if(a[i].second == 1) {
            long long x = a[i].first + k;
            ans = max(ans, x + a[j].first);
        } else {
            long long x = a[i].first;
            long long p = a[j].first;
            int need = (n + 1) / 2;
            long long l = a[j].first + 1, r = 10000000000ll;
            while(l <= r) {
                long long mid = l + (r - l) / 2;
                //at least need numbers >= mid
                int less = bin(a, mid);
                int more = n - (less + 1);
                if(i <= less) {
                } else {
                    more--;
                }

                int lneed = need - more;
                int bindex = bin1(b, less + 1);
                if(bindex + 1 >= lneed && get(bindex - lneed + 1, bindex) + k >= (mid * lneed)) {
                    p = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            ans = max(ans, p + x);
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
