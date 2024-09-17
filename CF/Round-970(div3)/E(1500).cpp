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



void solve() {
    int n;
    string s;
    cin >> n >> s;

    if(n % 2 == 0) {
        map<char, int> odd, even;
        int mx1 = 0, mx2 = 0;
        for(int i = 0; i < n; i++) {
            if(i % 2 == 0) {
                even[s[i]]++;
                mx1 = max(mx1, even[s[i]]);
            } else {    
                odd[s[i]]++;
                mx2 = max(mx2, odd[s[i]]);
            }
        }
        cout << n - (mx1 + mx2) << endl;
    } else {
        vector<vector<int>> preodd(n, vector<int>(26));
        vector<vector<int>> preeven(n, vector<int>(26));
        vector<vector<int>> postodd(n, vector<int>(26));
        vector<vector<int>> posteven(n, vector<int>(26));

        for(int i = 0; i < n; i++) {
            if(i % 2 == 0) {
                preeven[i][s[i] - 'a']++;
            } else {
                preodd[i][s[i] - 'a']++;
            }
            for(int j = 0; j < 26 && i > 0; j++) {
                preodd[i][j] += preodd[i - 1][j];
                preeven[i][j] += preeven[i - 1][j];
            }
        }

        for(int i = n - 1; i >= 0; i--) {
            if(i % 2 == 0) {
                posteven[i][s[i] - 'a']++;
            } else {
                postodd[i][s[i] - 'a']++;
            }
            for(int j = 0; j < 26 && i + 1 < n; j++) {
                postodd[i][j] += postodd[i + 1][j];
                posteven[i][j] += posteven[i + 1][j];
            }
        }

        int mx = 0;
        for(int i = 0; i < n; i++) {
            int mx1 = 0, mx2 = 0;
            for(int j = 0; j < 26; j++) {
                int c1 = 0;
                if(i > 0) {
                    c1 += preodd[i - 1][j];
                }
                if(i + 1 < n) c1 += posteven[i + 1][j];
                mx1 = max(mx1, c1);
            }

            for(int j = 0; j < 26; j++) {
                int c2 = 0;
                if(i > 0) {
                    c2 += preeven[i - 1][j];
                }
                if(i + 1 < n) c2 += postodd[i + 1][j];
                mx2 = max(mx2, c2);
            }
            //cout << i << " " << mx1 << " " << mx2 << endl;
            mx = max(mx, mx1 + mx2);
        }
        cout << (n - 1) - mx + 1 << endl;
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
