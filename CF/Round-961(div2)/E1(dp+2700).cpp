#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<unordered_set>
#include<string>
#include <string.h>

using namespace std;
using ll = long long;
const long long INF = 1e18;
const int N = 2010;
long long dp[N][2];

void reset(int n) {
  for(int i = 0; i <= n; i++) dp[i][0] = dp[i][1] = INF;
}

void solve() {
    int n;
    scanf("%d", &n);
    std :: vector<int> a(2 * n + 1);
    for(int i = 1; i <= 2 * n; i++) std :: cin >> a[i];

    if(n % 2 == 0) {
        long long mx = -1, mn = INF;
        for(int i = 1; i <= n; i += 2) {
            int A = a[i], B = a[i + n], C = a[i + 1], D = a[i + 1 + n];
            std :: vector<int> b = {A + C, A + D, B + C, B + D};
            std :: sort(b.begin(), b.end());
            mx = max(mx, b[2] + 0LL);
            mn = min(mn, b[1] + 0LL);
        }
         printf("%lld\n", mx - mn);
        return;
    } 
    
    if(n == 1) {
        printf("0\n");
        return;
    }

    long long ans = INF;

    std :: vector<int> A;
    for(int i = 1; i <= n; i++) {
        A.push_back(a[i]);
        A.push_back(a[i + n]);
    }
    
    //for(int x : A) std :: cout << x << " ";
    //std :: cout << std :: endl;
    //std :: cout << std :: endl;


    //generate all possible mins and do dp to minimize the max
    unordered_set<int> vis;
    for(int i = 0; i < n; i++) {
        std :: vector<int> mins;
        if(i != n - 1) {
            mins.push_back(A[i * 2] + A[(i + 1) * 2]);
            mins.push_back(A[i * 2] + A[(i + 1) * 2 + 1]);
            mins.push_back(A[i * 2 + 1] + A[(i + 1) * 2]);
            mins.push_back(A[i * 2 + 1] + A[(i + 1) * 2 + 1]);
        } else {
            mins.push_back(A[i * 2] + A[0]);
            mins.push_back(A[i * 2] + A[1]);
            mins.push_back(A[i * 2 + 1] + A[0]);
            mins.push_back(A[i * 2 + 1] + A[1]);
        }
        
        //Do DP to setup the maximum
        for(int minv : mins) {
            if(vis.find(minv) != vis.end()) continue;
            vis.insert(minv);
            //flip the first two or not
            for(int x = 0; x < 2; x++) {
                swap(A[0], A[1]);
                reset(n);
                dp[0][0] = dp[0][1] = minv; //0 : not flip, 1 : flip
                for(int j = 1; j < n; j++) {
                    if(j != n - 1 && j != 1) {
                        if(j % 2 == 1) {
                            //non flip
                            long long nonv1 = A[j * 2] + A[(j - 1) * 2];
                            long long nonv2 = A[j * 2] + A[(j - 1) * 2 + 1];
                            if(nonv1 >= minv) dp[j][0] = min(dp[j][0], max(dp[j - 1][0], nonv1));
                            if(nonv2 >= minv) dp[j][0] = min(dp[j][0], max(dp[j - 1][1], nonv2));
                            
                            //flip
                            long long f1 = A[j * 2 + 1] +  A[(j - 1) * 2];
                            long long f2 = A[j * 2 + 1] +  A[(j - 1) * 2 + 1];
                            if(f1 >= minv) dp[j][1] = min(dp[j][1], max(dp[j - 1][0], f1));
                            if(f2 >= minv) dp[j][1] = min(dp[j][1], max(dp[j - 1][1], f2));
                            
                            
                        } else {
                            //non flip
                            long long nonv1 = A[j * 2 + 1] + A[(j - 1) * 2 + 1];
                            long long nonv2 = A[j * 2 + 1] + A[(j - 1) * 2];
                            if(nonv1 >= minv) dp[j][0] = min(dp[j][0], max(dp[j - 1][0], nonv1));
                            if(nonv2 >= minv) dp[j][0] = min(dp[j][0], max(dp[j - 1][1], nonv2));
                            //flip
                            long long f1 = A[j * 2] +  A[(j - 1) * 2 + 1];
                            long long f2 = A[j * 2] +  A[(j - 1) * 2];
                            if(f1 >= minv) dp[j][1] = min(dp[j][1], max(dp[j - 1][0], f1));
                            if(f2 >= minv) dp[j][1] = min(dp[j][1], max(dp[j - 1][1], f2));
                        }
                        
                    } else if(j == 1) {
                        long long nonv1 = A[j * 2] + A[0];
                        if(nonv1 >= minv) dp[j][0] = min(dp[j][0], max(dp[j - 1][0], nonv1));
                        long long f1 = A[j * 2 + 1] + A[0];
                        if(f1 >= minv) dp[j][1] = min(dp[j][1], max(dp[j - 1][0], f1));
                    } 
                    else {
                        long long nonv1 = max(A[j * 2] + A[1], A[j * 2 + 1] + A[(j - 1) * 2 + 1]);
                        long long check1 = min(A[j * 2] + A[1], A[j * 2 + 1] + A[(j - 1) * 2 + 1]);
                        if(check1 >= minv) dp[j][0] = min(dp[j][0], max(dp[j - 1][0], nonv1));
                        long long nonv2 = max(A[j * 2] + A[1], A[j * 2 + 1] + A[(j - 1) * 2]);
                        long long check2 = min(A[j * 2] + A[1], A[j * 2 + 1] + A[(j - 1) * 2]);
                        if(check2 >= minv) dp[j][0] = min(dp[j][0], max(dp[j - 1][1], nonv2));

                        long long f1 =  max(A[j * 2 + 1] + A[1], A[j * 2] + A[(j - 1) * 2 + 1]);
                        long long check3 = min(A[j * 2 + 1] + A[1], A[j * 2] + A[(j - 1) * 2 + 1]);
                        if(check3 >= minv) dp[j][1] = min(dp[j][1], max(dp[j - 1][0], f1));
                        long long f2 = max(A[j * 2 + 1] + A[1], A[j * 2] + A[(j - 1) * 2]);
                        long long check4 = min(A[j * 2 + 1] + A[1], A[j * 2] + A[(j - 1) * 2]);
                        if(check4 >= minv) dp[j][1] = min(dp[j][1], max(dp[j - 1][1], f2));
                    }
                }
                ans = min(ans, dp[n - 1][0] - minv);
                ans = min(ans, dp[n - 1][1] - minv);
            }
        }
    }

    printf("%lld\n", ans);
}    

int main() {
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
