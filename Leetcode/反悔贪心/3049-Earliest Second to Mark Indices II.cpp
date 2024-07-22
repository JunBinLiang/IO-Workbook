class Solution {
public:
    int earliestSecondToMarkIndices(vector<int>& nums, vector<int>& changeIndices) {
        for(auto& ind : changeIndices) ind--;
        int l = 1, r = changeIndices.size(), ans = -1;        
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(ok(nums, changeIndices, mid)) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return ans;
    }
    
    bool ok(vector<int>& a, vector<int>& b, int mid) {
        int n = a.size();
        vector<bool> vis(n + 1);
        vector<bool> take(b.size());
        for(int i = 0; i < mid; i++) {
            if(a[b[i]] && !vis[b[i]]) {
                take[i] = true;
                vis[b[i]] = true;
            }
        }
        
        priority_queue<int> pq;
        int empty = 0; long long s = 0;
        
        for(int i = mid - 1; i >= 0; i--) {
            if(take[i]) {
                if(pq.size() + 1 <= empty) { //can add
                    pq.push(-a[b[i]]);
                    s += a[b[i]];
                } else {
                    if(pq.size() > 0 && a[b[i]] > -pq.top()) {
                        s -= (-pq.top());
                        pq.pop();
                        s += a[b[i]];
                        pq.push(-a[b[i]]);
                        empty++;
                    } else {
                        empty++;
                    }
                }
            } else {
                empty++;
            }
        }
        long long need = n;
        for(int i = 0; i < a.size(); i++) need += a[i];  
        need -= s;
        return need <= empty;
    }
};
