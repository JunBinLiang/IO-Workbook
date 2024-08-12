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
//4:42
void solve() {
    int n;
    cin >> n;
    int m = (n - 1) * n / 2;
    vector<int> b(m);
    vector<int> a;
    for(int i = 0; i < m; i++) cin >> b[i];
    sort(b.begin(), b.end());

    int toPair = n - 1;
    for(int i = 0; i < m; i++) {
        int j = i;
        int count = 0;
        while(j < m && b[j] == b[i]) {
            count++;
            j++;
        }

        while(count > 0) {
            count -= toPair;
            toPair--;
            a.push_back(b[i]);
        }

        i = j - 1;
    }
    a.push_back(1000000000);
    for(int i : a) cout << i << " ";
    cout << endl;
}    

int main() {
    int t = 1;
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
