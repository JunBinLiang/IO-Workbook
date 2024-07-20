#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<string>
#include <string.h>

using namespace std;
using ll = long long;

const int N = 5e5 + 10;
int a[N];
int L[N], R[N];
long long lchange[N], rchange[N], llchange[N], rrchange[N];
long long ans[N];
vector<int> leftnodes[N], rightnodes[N];
int n;
void test() {
    long long s = 0;
    for(int i = 1; i <= n; i++) {
        int v = a[i];
        for(int j = i; j <= n; j++) {
            v = min(v, a[j]);
            s += v;
        }
    }
    cout << s << endl;
}

void solve() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    a[0] = a[n + 1] = -1;

    for(int i = 0; i <= n + 1; i++) {
        L[i] = R[i] = -1;
        lchange[i] = rchange[i] = 0;
        llchange[i] = rrchange[i] = 0;
        leftnodes[i].clear();
        rightnodes[i].clear();
    }

    vector<int> stk;
    for(int i = 1; i <= n + 1; i++) {
        while(stk.size() > 0 && a[i] < a[stk.back()]) {
            R[stk.back()] = i;
            stk.pop_back();
        }
        stk.push_back(i);
    }
    stk.clear();
    for(int i = n; i >= 0; i--) {
        while(stk.size() > 0 && a[i] < a[stk.back()]) {
            L[stk.back()] = i;
            stk.pop_back();
        }
        stk.push_back(i);
    }

    set<pair<int, int>> ls, rs; 
    vector<int> count1(n + 2), count2(n + 2);
    for(int i = 1; i <= n + 1; i++) {
        vector<pair<int, int>> temp;
        for(auto p : ls) {
            if(-p.first < a[i]) break;
            int index = p.second;
            count1[index]++;
            if(count1[index] == 2) {
                temp.push_back(p);
            }   
        }
        for(auto& p : temp) {
            int index = p.second;
            int p1 = i - 1;
            int lsz = index - L[index] - 1;
            rrchange[index] = ((p1 - R[index] + 0ll) * (lsz + 1) * a[index]);
            ls.erase(p);
        }
        ls.insert({-a[i], i});
    }

    for(int i = n; i >= 0; i--) {
        vector<pair<int, int>> temp;
        for(auto p : rs) {
            if(-p.first < a[i]) break;
            int index = p.second;
            count2[index]++;
            if(count2[index] == 2) {
                temp.push_back(p);
            }   
        }

        for(auto& p : temp) {
            int index = p.second;
            int p2 = i + 1;
            int rsz = R[index] - index - 1;
            llchange[index] = ((L[index] - p2 + 0ll) * (rsz + 1) * a[index]);
            rs.erase(p);
        }
        rs.insert({-a[i], i});
    }

    long long s = 0;
    for(int i = 1; i <= n; i++) {
        int lsz = i - L[i] - 1, rsz = R[i] - i - 1;
        leftnodes[R[i]].push_back(i);
        rightnodes[L[i]].push_back(i);
        s += ((lsz + 1ll) * (rsz + 1ll) * a[i]);
        if(lsz > 0)
          lchange[i] = -((rsz + 1ll) * a[i]); //remove 1 left element
        if(rsz > 0)
          rchange[i] = -((lsz + 1ll) * a[i]); //remove 1 right element
    }
    
    for(int i = 1; i <= n; i++) {
      ans[i] = s;
      int lsz = i - L[i] - 1, rsz = R[i] - i - 1;
      ans[i] -= ((lsz + 1ll) * (rsz + 1ll) * a[i]);
    }
    
    long long change = 0;
    ls.clear();
    rs.clear();
    for(int i = 1; i <= n + 1; i++) {
        for(int index : leftnodes[i]) {
            ans[i] += rrchange[index];
            change -= rchange[index];
        }

        while(ls.size() > 0) {
            auto it = ls.begin();
            if(-(it -> first) > i) {
                int index = it -> second;
                change += rchange[index];
                ls.erase(*it);
            } else {
                break;
            }
        }
        ls.insert({-R[i], i});
        ans[i] += change;
    }

    change = 0;
    for(int i = n ; i >= 0; i--) {
        for(int index : rightnodes[i]) {
            ans[i] += llchange[index];
            change -= lchange[index];
        }

        while(rs.size() > 0) {
            auto it = rs.begin();
            if(it -> first < i) {
                int index = it -> second;
                change += lchange[index];
                rs.erase(*it);
            } else {
                break;
            }
        }
        rs.insert({L[i], i});
        ans[i] += change;
    }

    for(int i = 1; i <= n; i++) {
        printf("%lld ", ans[i]);
    }
    printf("\n");
}    

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
