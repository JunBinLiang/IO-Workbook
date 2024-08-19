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

//Find the MST or XOR => Use Boruvka’s algorithm
//https://www.geeksforgeeks.org/boruvkas-algorithm-greedy-algo-9/
const int N = 2e3 + 100;
vector<int> g[N], components[N];
int color[N], p[N];

int id = 1;
int tr[N * 32][2];
int cnt[N * 32 * 2];
unordered_set<int> leafs[N * 32 * 2];

void add(int index, int n) {
    int u = 0;
    for(int i = 30; i >= 0; i--) {
        int b = 0;
        if(n & (1 << i)) b = 1;
        if(tr[u][b] == -1) {
            tr[u][b] = id++;
        }
        u = tr[u][b];
        cnt[u]++;
    }
    leafs[u].insert(index);
}

void del(int index, int n) {
    int u = 0;
    for(int i = 30; i >= 0; i--) {
        int b = 0;
        if(n & (1 << i)) b = 1;
        u = tr[u][b];
        cnt[u]--;
    }
    leafs[u].erase(index);
}

pair<int, int> query(int n) {
    int u = 0;
    int ans = 0;
    for(int i = 30; i >= 0; i--) {
        int b = 0;
        if(n & (1 << i)) b = 1;
        if(tr[u][b] != -1 && cnt[tr[u][b]] > 0) {
            u = tr[u][b];
        } else {
            u = tr[u][b ^ 1];
            ans += (1 << i);
        }
    }
    auto& leaf = leafs[u];
    return {ans, *(leaf.begin())};
}

int find(int u) {
    return p[u] == u ? u : p[u] = find(p[u]);
}

void dfs(int u) { //dfs color
    for(int v : g[u]) {
        if(color[v] == -1) {
            color[v] = color[u] ^ 1;
            dfs(v);
        }
    }
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    //init
    memset(color, -1, sizeof color);
    memset(tr, -1, sizeof tr);
    memset(cnt, 0, sizeof cnt);
    for(int i = 0; i < n; i++) g[i].clear();
    for(int i = 0; i < n; i++) p[i] = i;

    //add all to Trie
    for(int i = 0; i < n; i++) add(i, a[i]);

    while(true) { //each iteration will reduce at least half components
        //find al component first
        for(int i = 0; i < n; i++) components[i].clear();
        unordered_set<int> us;
        for(int i = 0; i < n; i++) {
            int r = find(i);
            components[r].push_back(i);
            us.insert(r);
        }

        if(us.size() == 1) break;

        vector<pair<int, int>> merge;
        for(int i = 0; i < n; i++) {
            if(components[i].size() == 0) continue;
            for(int index : components[i]) {
                del(index, a[index]);
            }
            
            long long mn = 1000000000000ll;
            pair<int, int> mergePair = {-1, -1};
            for(int index : components[i]) {
                pair<int, int> pa = query(a[index]);
                if(pa.first < mn) {
                    mn = pa.first;
                    mergePair = {index, pa.second};
                }
            } 
            merge.push_back(mergePair);
            for(int index : components[i]) {
                add(index, a[index]);
            }
        }

        for(auto& e : merge) {
            int u = e.first, v = e.second;
            int r1 = find(u), r2 = find(v);
            if(r1 != r2) {
                p[r1] = r2;
                g[u].push_back(v);
                g[v].push_back(u);
            }
        }
    }

    color[0] = 0;
    dfs(0);
    for(int i = 0; i < n; i++) {
        cout << color[i];
    }
    cout << endl;
}    

int main() {
    int t = 1;
    //std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
