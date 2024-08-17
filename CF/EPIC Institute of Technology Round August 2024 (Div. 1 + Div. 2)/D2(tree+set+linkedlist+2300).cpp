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

template <typename T>
ostream &operator<<(ostream &out, const set<T> &a)
{
  out << "[";
  bool first = true;
  for (auto v : a)
  {
    out << (first ? "" : ", ");
    out << v;
    first = 0;
  }
  out << "]";
  return out;
}

const int N = 3e5 + 10;
vector<int> g[N];
set<int> childs[N];
int p[N], rp[N], sz[N], fa[N];
int cnt1 = 0, cnt2 = 0; 
int chain = 0;
int n, m;
int x = 0;
void dfs(int u) {
    sz[u] = 1;
    for(int v : g[u]) {
        dfs(v);
        sz[u] += sz[v];
    }
}

void remove(int val, int pos) {
    set<int>& s = childs[fa[val]];
    auto it = s.find(pos);
    p[pos] = -100;
    rp[val] = -100;
    
    bool removeFirst = (it == s.begin());
    if(childs[val].size() > 0) {
        int firstchild = *(childs[val].begin());
        if(firstchild == pos + 1) {
            cnt2--;
        }
    }
    
    if(removeFirst && p[pos - 1] == fa[val]) {
        cnt2--;
    }

    it++;
    if(it == s.end()) {
        cnt1--;
    } else {
        if(pos + sz[val] == *it) {
            cnt1--;
        }
    }
    s.erase(pos);
    
    if(s.size() > 0 && removeFirst) {
        int nextp = *s.begin();
        int nextv = p[nextp];
        if(nextv >= 0 && p[nextp - 1] == fa[nextv]) {
            cnt2++;
        }
    }
    
    //previous
    it = s.upper_bound(pos);
    if(it != s.begin()) {
        it--;
        int ppos = *it;
        int pval = p[ppos];
        //previous
        if(ppos + sz[pval] == pos) {
            cnt1--;
        }
        it++;
        if(it == s.end()) {
            cnt1++;
        } else {
            if(*it == ppos + sz[pval]) {
                cnt1++;
            }
        }
    } 
}

void add(int val, int pos) {
    set<int>& s = childs[fa[val]];
    p[pos] = val;
    rp[val] = pos;
    
    if(childs[val].size() > 0) {
        int firstchild = *(childs[val].begin());
        if(firstchild == pos + 1) {
            cnt2++;
        }
    }
    
    if(s.size() == 0) {
        cnt1++;
        if(p[pos - 1] == fa[val]) {
            cnt2++;
        }
        s.insert(pos);
        return;
    }

    auto it = s.upper_bound(pos);
    int nextp = *it;
    if(it == s.begin()) { //insert to the begining
        if(p[pos - 1] == fa[val]) {
            cnt2++;
        }

        int nextpos = *it;
        int nextv = p[nextpos];
        if(nextv >= 0 && p[nextpos - 1] == fa[nextv]) {
            cnt2--;
        }

        if(it != s.end()) { //has next
            if(pos + sz[val] == *it) {
                cnt1++;
            }
        }
    } else {
        it--;
        int ppos = *it;
        int pval = p[ppos]; 
        if(ppos + sz[pval] == pos) {
            cnt1++;
        }
        
        if(ppos + sz[pval] == nextp) {
            cnt1--;
        }

        it = s.upper_bound(pos);
        if(it != s.end()) {
            if(pos + sz[val] == *it) {
                cnt1++;
            }
        } else { //add to the end
          
        }
    }
    s.insert(pos);
}


void solve() {
    scanf("%d%d", &n, &m);
    cnt1 = 0; cnt2 = 0; chain = 0;
    for(int i = 0; i <= n; i++) {
        g[i].clear();
        childs[i].clear();
    }
    vector<int> pp(n + 1);
    fa[1] = 0;
    for(int i = 2; i <= n; i++) {
        int pa;
        scanf("%d", &pa);
        g[pa].push_back(i);
        fa[i] = pa;
    }

    for(int i = 1; i <= n; i++) {
        scanf("%d", &p[i]);
        pp[i] = p[i];
        rp[p[i]] = i; //reverse
        childs[fa[p[i]]].insert(i);
    }

    for(int i = 0; i <= n; i++) {
        if(childs[i].size() > 0) {
            chain++;
        }
    }
    dfs(1);

    for(int i = 1; i <= n; i++) {
        set<int>& s = childs[fa[i]];
        auto it = s.find(rp[i]); //to next
        it++;
        if(it == s.end()) { //already last
            cnt1++;
        } else {
            if(*it == rp[i] + sz[i]) {
                cnt1++;
            }
        }
    }

    for(int i = 0; i <= n; i++) {
        auto& s = childs[i];
        if(s.size() > 0) {
            int firstp = *(s.begin());
            if(i == p[firstp - 1]) cnt2++;
        }
    }
    
    

    

    for(int i = 0; i < m; i++) {
        x++;
        int pi, pj;
        scanf("%d%d", &pi, &pj);
        
        int p1 = p[pi], p2 = p[pj];
        remove(p1, pi);
        remove(p2, pj);
        add(p1, pj);
        add(p2, pi);
        
        if(cnt1 == n && cnt2 == chain ) {
            printf("YES\n");
        } else {
            printf("NO\n");
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
