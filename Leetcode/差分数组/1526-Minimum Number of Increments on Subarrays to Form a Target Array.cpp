class Solution {
public:
    int minNumberOperations(vector<int>& a) {
        a.push_back(0);
        int ans = 0;
        for(int i = 0; i < a.size(); i++) {
            int diff = a[i];
            if(i) diff -= a[i - 1];
            if(diff < 0) ans += -diff;
        }
        return ans;
    }
};
