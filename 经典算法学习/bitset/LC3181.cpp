const int N = 1e5 + 10;
bitset<100000 + 5> dp;
bitset<100000 + 5> cur;
bitset<100000 + 5> c;
class Solution {
public:
    int maxTotalReward(vector<int>& a) {
        sort(a.begin(), a.end());
        int n = a.size();
        int s = a.back() * 2 + 1;
        
        dp &= 0;
        cur &= 0;
        dp |= 1;
        
        
        int j = 0;
        for(int i = 0; i < n; i++) {
            int v = a[i];
            while(j < v) {
                cur.flip(j);
                j++;
            }
            c = dp & cur;
            dp = dp | (c << v);
        }
        
        int res = 0;
        for(int i = 0; i <= s; i++) {
            if(dp.test(i)) {
                res = i;
            }
        }
        
        return res;
    }
};
