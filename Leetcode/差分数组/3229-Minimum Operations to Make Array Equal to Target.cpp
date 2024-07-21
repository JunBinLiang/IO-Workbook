class Solution {
public:
    long long minimumOperations(vector<int>& a, vector<int>& b) {
        int n = a.size() + 1;
        a.push_back(0);
        b.push_back(0);
        
        long long add = 0, sub = 0, ans = 0;
        for(int i = 0; i < n; i++) {
            int diff1 = a[i];
            int diff2 = b[i];
            if(i > 0) {
                diff1 -= a[i - 1];
                diff2 -= b[i - 1];
            }
            if(diff1 < diff2) {
                add += (diff2 - diff1);
            } else {
                sub += (diff1 - diff2);
            }
        }
        return max(add, sub);
    }
};
