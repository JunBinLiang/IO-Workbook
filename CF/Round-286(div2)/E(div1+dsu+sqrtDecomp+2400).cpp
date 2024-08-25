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
const int N = 1e5 + 10, M = 1e5 + 10;
int SQ;
pair<int, int> q[M];
pair<int, pair<int, int>> e[M], e2[M];
bool skip[M];
map<pair<int, int>, int> mp;
unordered_map<int, int> p;

int find(int u) {
    if(p[u] == u) return u;
    int root = find(p[u]);
    p[u] = root;
    return root;
}

void solve() {
    int n, m, t;
    scanf("%d%d", &n, &m);
    memset(skip, 0, sizeof skip);
    SQ = (int)(sqrt(n));
    for(int i = 0; i < m; i++) {
        scanf("%d%d%d", &e[i].second.first, &e[i].second.second, &e[i].first);
        e2[i] = e[i];
    }
    scanf("%d", &t);
    for(int i = 0; i < t; i++) {
        scanf("%d%d", &q[i].first, &q[i].second);
        if(q[i].first > q[i].second) swap(q[i].first, q[i].second);
        if(mp.find(q[i]) != mp.end()) {
            skip[i] = true;
            continue;
        }
        mp[q[i]] = 0;
    }

    sort(e, e + m);
    for(int i = 0; i < m; i++) {
        int j = i;
        vector<pair<int, int>> temp;
        unordered_set<int> vertexs;
        while(j < m && e[i].first == e[j].first) {
            temp.push_back(e[j].second);
            vertexs.insert(e[j].second.first);
            vertexs.insert(e[j].second.second);
            j++;
        }

        //Union Find
        p.clear();
        for(auto& pa : temp) {
            int u = pa.first, v = pa.second;
            if(p.find(u) == p.end()) p[u] = u;
            if(p.find(v) == p.end()) p[v] = v;
            int r1 = find(u), r2 = find(v);
            if(r1 != r2) {
                p[r1] = r2;
            }
        }

        if(temp.size() > SQ) {
            for(int k = 0; k < t; k++) {
                if(skip[k]) continue;
                int u = q[k].first, v = q[k].second;
                if(p.find(u) == p.end()) p[u] = u;
                if(p.find(v) == p.end()) p[v] = v;
                int r1 = find(u), r2 = find(v);
                if(r1 == r2) {
                    mp[q[k]]++;
                }
            }
        } else {
            vector<int> ver(vertexs.begin(), vertexs.end());
            for(int x = 0; x < ver.size(); x++) {
                for(int y = x + 1; y < ver.size(); y++) {
                    int u = ver[x], v = ver[y];
                    if(u > v) swap(u, v);
                    if(mp.find({u, v}) != mp.end()) {
                        if(p.find(u) == p.end()) p[u] = u;
                        if(p.find(v) == p.end()) p[v] = v;
                        int r1 = find(u), r2 = find(v);
                        if(r1 == r2) {
                            mp[{u, v}]++;
                        }
                    }
                }
            }
        }
        i = j - 1;
    }


    for(int i = 0; i < t; i++) {
        int ans = mp[q[i]];
        printf("%d\n", ans);
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
