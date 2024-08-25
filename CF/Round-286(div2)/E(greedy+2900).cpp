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

const int N = 1e5 + 10;
long long cur[N];
bool ok(vector<pair<long long, long long>>& a, long long m, long long k, long long p, long long mid) {
    /*
        Do it reverse:
        1. Assume each bambo start as "mid"
        2. Each day it will decrease a[i].second
        3. You can increase p at most k time each day.
        4. Make sure at the end, it is at least a[i].first and it does not become negative at any moment
    */
    
    int n = a.size();
    priority_queue<pair<long long, int>> pq;
    for(int i = 0; i < n; i++) {
        cur[i] = mid;
        if(cur[i] - a[i].second * m >= a[i].first) continue;
        long long d = (cur[i] / a[i].second);
        pq.push({(m - d + 1), i});
        //if(mid == 10)cout <<"gg " << m - d + 1 << endl;
    }

    for(int d = m; d >= 1; d--) {
        vector<pair<long long, int>> b;
        for(int i = 0; i < k && pq.size() > 0; i++) {
            auto pa = pq.top(); pq.pop();
            int j = pa.second;
            cur[j] += p;
            if(cur[j] - a[j].second * m >= a[j].first) continue;
            long long newd = (cur[j] / a[j].second);
            pq.push({(m - newd + 1), j});
        }

        if(pq.size() > 0 && pq.top().first >= d) {
            return false;
        }
        for(auto& pa : b) {
            if(pa.first >= d) {
                return false;
            }
            pq.push(pa);
        }
    }
    return pq.size() == 0;
}

void solve() {
    int n, m, k, p;
    cin >> n >> m >> k >> p;
    vector<pair<long long, long long>> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }

    long long l = 0, r = 10000000000000ll;
    for(int i = 0; i < n; i++) l = max(l, a[i].second);
    long long ans = -1;
    while(l <= r) {
        long long mid = l + (r - l) / 2;
        if(ok(a, m, k, p, mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans << endl;
}    

int main() {
    int t = 1;
    //std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
