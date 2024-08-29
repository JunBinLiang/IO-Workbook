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
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <bits/stdc++.h>


using namespace std;
const int N = 2e5 + 10;
vector<pair<int, int>> q[N];
vector<pair<int, int>> a;
int b[N];

using namespace __gnu_pbds;
template<class TIn, class TOut = null_type>
using order_tree = tree<TIn, TOut, less<TIn>, rb_tree_tag,
	tree_order_statistics_node_update>;
order_tree<int> tr;

void solve() {
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        a.push_back({x, i});
        b[i] = x;
    }

    for(int j = 0; j < m; j++) {
        int i, k;
        scanf("%d%d", &i, &k);
        q[k].push_back({i, j});
    }

    sort(a.begin(), a.end());
    for(int i = 0; i <= n; i++) {
        sort(q[i].begin(), q[i].end());
        reverse(q[i].begin(), q[i].end());
    }

    tr.insert(0);
    for(int i = 1; i <= n; i++) tr.insert(i);
    
    vector<int> lastPos(n + 1);
    vector<bool> ans(m);
    int j = 0;
    for(int level = 1; level <= n; level++) {
        for(int k = 1; k <= n; k++) {
            int p = lastPos[k];
            if(p > n) break;
            int ord = tr.order_of_key(p);
            int sub = 0;
            if(tr.find(p) == tr.end()) sub = 1;
            auto it = tr.find_by_order(ord + k - sub);
            if(it == tr.end()) {
                lastPos[k] = n + 10;
            } else {
                lastPos[k] = *it;
            }
            while(q[k].size() > 0 && q[k].back().first <= lastPos[k]) {
                pair<int, int>& pa = q[k].back(); q[k].pop_back();
                int i = pa.first, index = pa.second;
                if(b[i] >= level) {
                    ans[index] = true;
                }
            }
        }

        //remove
        while(j < a.size() && a[j].first <= level) {
            tr.erase(a[j].second);
            j++;
        }
    }


    for(int i = 0; i < m; i++) {
        if(ans[i]) printf("YES\n");
        else printf("NO\n");
    }    
}    

int main() {
    int t = 1;
    //std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
