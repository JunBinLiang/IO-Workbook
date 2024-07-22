bool comp(vector<int>& p1, vector<int>& p2) {
    return p1[1] < p2[1];
}

class Solution {
public:
    int scheduleCourse(vector<vector<int>>& a) {
        int ans = 0;
        sort(a.begin(), a.end(), comp);
        priority_queue<int> pq;
        int tot = 0;
        for(int i = 0; i < a.size(); i++) {
            if(tot + a[i][0] <= a[i][1]) {
                tot += a[i][0];
                pq.push(a[i][0]);
            } else {
                if(pq.size() > 0 && a[i][0] < pq.top()) {
                    tot -= pq.top(); pq.pop();
                    tot += a[i][0];
                    pq.push(a[i][0]);
                }
            }
            ans = max(ans, (int)(pq.size()));
        }
        
        return ans;
    }
};
