#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
#include<unordered_set>
#include<map>
#include<string>
#include <string.h>
#include <bitset>
#include <queue>

using namespace std;

const int N = 2e5 + 10;
long long p[N];
int a[N];
long long get(int l, int r) {
    return l == 0 ? p[r] : p[r] - p[l - 1];
}

int toright(long long val, int i, int n) {
    int po = -1;
    int l = i + 1, r = n - 1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(get(i + 1, mid) <= val) {
            po = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return po;
}

int toright1(int val, int i, int n) {
    int l = i, r = n;
    int ans = -1;
    while(l <= r) {
        int mid = l + (r - l ) / 2;
        if(get(i, mid) >= val) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

int toleft(long long val, int i, int n) {
    int l = 0, r = i - 1;
    int po = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(get(mid, i - 1) <= val) {
            po = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    return po;
}

void solve() {
    int n, m, ans = 0;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    if(n == 1) {
        printf("1\n");
        return;
    }

    for(int i = 0; i < n; i++) {
        p[i] = a[i];
        if(i) p[i] += p[i - 1];
    }

    priority_queue<int, vector<int>, greater<int>> complete; 
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pending; 
    for(int i = 0; i < n; i++) {
        long long cur = a[i];
        int left = i;
        while(true) {
            int l = toleft(cur, left, n);
            if(l == -1) {
                break;
            } else {
                cur = get(l, i);
                left = l;
            }
        }   
        
        if(left == 0) {
            int right = toright(cur, i, n);
            if(right == -1) right = i + 1;
            else right++;
            complete.push(right);
        } else {
            int right = i;
            while(true) {
                int r = toright(cur, right, n);
                if(r == -1) {
                    break;
                } else {
                    cur = get(left, r);
                    right = r;
                    if(cur >= a[left - 1]) break;
                }
            }

            if(cur >= a[left - 1]) { //can add to the pending queue
                pending.push({toright1(a[left - 1], left, n), left});
            }
        }
  
        while(complete.size() > 0 && complete.top() == i) {
            int r = complete.top(); complete.pop();
            long long cur = get(0, r - 1);
            int right = toright(cur, r - 1, n);
            if(right != -1) {
                right++;
                complete.push(right);
            }
        }
        

        while(pending.size() > 0 && pending.top().first == i) {
            pair<int, int> p = pending.top(); pending.pop();
            int R = p.first, L = p.second; 
            long long cur = get(L, R);
            
            while(true) {
                int l = toleft(cur, L, n);
                if(l == -1) {
                    break;
                } else {
                    cur = get(l, R);
                    L = l;
                }
            }   

            if(L == 0) {
                int right = toright(cur, R, n);
                if(right == -1) right = i + 1;
                else right++;
                complete.push(right);
            } else {
                int right = R;
                while(true) {
                    int r = toright(cur, right, n);
                    if(r == -1) {
                        break;
                    } else {
                        cur = get(L, r);
                        right = r;
                        if(cur >= a[L - 1]) break;
                    }
                }
                if(cur >= a[L - 1]) { //can add to the pending queue
                    pending.push({toright1(a[L - 1], L, n), L});
                }
            }
        }
        
        printf("%d ", (int)(complete.size()));
    }
    printf("\n");
}    

int main() {
    int t = 1;
    std :: cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
