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

bool allzero(vector<int>& a) {
    for(int i : a) {
        if(i != 0) return false;
    }
    return true;
}

int dfs(vector<int>& a, int n) {
    if(n == 0) {
        if(allzero(a)) return 0;
        else return 1;
    }
    bool ok = true;
    for(int i = 0; i < a.size(); i++) {
        if(a[i] != a[(i + n / 2) % a.size()]) {
            ok = false;
            break;
        }
    }


    if(ok) {
        return dfs(a, n / 2);
    } else {
        vector<int> b(a.size());
        for(int i = 0; i < a.size(); i++) {
            b[i] = a[i] ^ a[(i + n / 2) % a.size()];
        }
        for(int i = 0; i < a.size(); i++) {
            a[i] = b[i];
        }
        return n / 2 + dfs(a, n / 2);
    }
}

void solve() {
    int n;
    scanf("%d", &n);
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    cout << dfs(a, n) << endl;
}    

int main() {
    int t = 1;
    //std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
