#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

using ll = long long;
#define pb push_back
#define ve vector


const int N = 1e5 + 10;
int a[N];
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> b(n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }

    sort(b.begin(), b.end());
    int v = b[0];
    for(int i = 0; i < n; i++) {
        if(a[i] != b[i]) {
            if(a[i] % v != 0) {
                cout << "NO" << endl;
                return;
            }
        }
    }
    cout << "YES" << endl;
}

int main()
{   
    int t = 1;
    cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}
