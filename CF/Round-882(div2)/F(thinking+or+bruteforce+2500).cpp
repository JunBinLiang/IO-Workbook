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

const int N = 2e5 + 10;
pair<int, long long> last[N];
pair<int, long long> cur[N];
int sz = 0;
void rebuild() {
    int index = 0;
    for(int i = 0; i < sz; i++) {
        int j = i;
        while(j < sz && cur[j].first == cur[i].first) {
            j++;
        }
        if(j - i == 1) {
            cur[index++] = cur[i];
        } else {
            cur[index++] = cur[i];
            cur[index++] = cur[ j - 1];
        }
        i = j - 1;
    }
    sz = index;
}

void solve() {
    int n, m;
    scanf("%d%d", &n, &m);
    sz = n;
    vector<pair<int, long long>> b;
    
    for(int i = 0; i < n; i++) {
        scanf("%d", &cur[i].first);
        cur[i].second = i + 1;
    }
    rebuild();
    
    unordered_set<int> s;
    for(int i = 0; i < sz; i++) {
        if(s.find(cur[i].first) != s.end()) continue;
        s.insert(cur[i].first);
        b.push_back(cur[i]);
    }
        
    int lastIndex = 0;
    for(int i = 0; i < sz; i++) {
        last[lastIndex++] = cur[i];
    }
    
    vector<vector<pair<int, long long>>> all;
    vector<pair<int, long long>> endv;
    endv.push_back(cur[sz - 1]);
    
    for(int t = 1; t <= n - 1; t++) {
        sz = 0;
        if(t > 1) {
            cur[sz++] = {endv[t - 2].first | last[0].first, endv[t - 2].second + n};
        }
        for(int i = 1; i < lastIndex; i++) {
            if(last[i].second == last[i - 1].second + 1) {
                cur[sz++] = {last[i].first | last[i - 1].first, last[i - 1].second + n};
            } else {
               cur[sz++] = {last[i - 1].first, last[i - 1].second + n};
               cur[sz++] = {last[i - 1].first, last[i].second + n - 1};
            }
        }
        rebuild();
        if(sz == 0) break;
        
        endv.push_back(cur[sz - 1]);
        for(int i = 0; i < sz; i++) {
            last[i] = cur[i];
            if(s.find(cur[i].first) != s.end()) continue;
            s.insert(cur[i].first);
            b.push_back(cur[i]);
        }
        lastIndex = sz;
    }

    

    sort(b.begin(), b.end());
    for(int i = b.size() - 1; i >= 0; i--) {
        if(i + 1 < b.size()) {
            b[i].second = min(b[i].second, b[i + 1].second);
        }
    }
    
    while(m--) {
        int k;
        scanf("%d", &k);
        if(k >= b.back().first) {
            printf("-1\n");
        } else {
            int l = 0, r = b.size() - 1;
            int p = -1;
            while(l <= r) {
                int mid = l + (r - l) / 2;
                if(b[mid].first > k) {
                    p = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            printf("%lld\n", b[p].second);
        }
    }
}    

int main() {
    int t = 1;
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
