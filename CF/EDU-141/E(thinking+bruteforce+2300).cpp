#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<unordered_set>
#include<string>
#include <string.h>

using namespace std;
using ll = long long;

int get(std :: vector<int>& p, int l, int r) {
    if(l > r) return 0;
    return l == 0 ? p[r] : p[r] - p[l - 1];
}

void solve() {
    int n;
    std :: cin >> n;
    std :: vector<int> a(n), b(n), ans;
    for(int i = 0; i < n; i++) std :: cin >> a[i];
    for(int i = 0; i < n; i++) std :: cin >> b[i];

    std :: vector<int> p1(n + 1), p2(n + 1);
    int k = 0;
    for(int i = 0; i < n; i++) {
        if(a[i] > b[i]) {
            p1[b[i]]++;
            p2[a[i]]++;
            k++;
        }
    }
    
    for(int i = 1; i <= n; i++) p1[i] += p1[i - 1];
    for(int i = 1; i <= n; i++) p2[i] += p2[i - 1];
    
    
    /*for(int i = 0; i <= n; i++) cout << p1[i] << "  ";
    cout << endl;
    for(int i = 0; i <= n; i++) cout << p2[i] << "  ";
    cout << endl;
    
    cout << k << endl;*/
    
    for(int i = 1; i <= n; i++) {
        int s = 0;
        for(int j = 1; j <= n; j += i) {
            int l = j, r = min(j + i - 1, n);
            int s1 = get(p2, 0, l - 1);
            int s2 = get(p1, 0, l - 1);
            int s3 = get(p2, l, r) - (s2 - s1);
            s += s3;
        }
        if(s == k) {
            ans.push_back(i);
        }
    }
    std :: cout << ans.size() << std :: endl;
    for(int x : ans) std :: cout << x << " ";
    std :: cout << endl;
}    

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
