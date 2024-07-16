class Solution {
public:
    int findCrossingTime(int n, int k, vector<vector<int>>& time) {
        int t = 0;

        priority_queue<pair<int, int>> leftWait, rightWait;
        set<pair<int, int>> leftWork, rightWork;
        for(int i = 0; i < k; i++) {
            leftWait.push({time[i][0] + time[i][2], i});
        }
        
        while(n > 0 || rightWait.size() > 0 || rightWork.size() > 0) {
            //The bridge is empty currently
            while(leftWork.size() > 0 && leftWork.begin() -> first <= t) {
                auto it = leftWork.begin();
                int i = it -> second;
                leftWork.erase(*it);
                leftWait.push({time[i][0] + time[i][2], i});
            }
            while(rightWork.size() > 0 && rightWork.begin() -> first <= t) {
                auto it = rightWork.begin();
                int i = it -> second;
                rightWork.erase(*it);
                rightWait.push({time[i][0] + time[i][2], i});
            }
            
            if(rightWait.size() > 0) {
                auto p = rightWait.top(); rightWait.pop();
                int i = p.second;
                t += time[i][2]; //cross to left
                leftWork.insert({t + time[i][3], i});
            } else if(n > 0 && leftWait.size() > 0){
                auto p = leftWait.top(); leftWait.pop();
                int i = p.second;
                t += time[i][0]; //cross to right
                rightWork.insert({t + time[i][1], i});
                n--;
            } else if(leftWork.size() > 0 || rightWork.size() > 0) {
                if(leftWork.size() > 0 && rightWork.size() > 0) {
                    t = min(leftWork.begin() -> first, rightWork.begin() -> first); 
                } else if(leftWork.size() > 0) {
                    t = leftWork.begin() -> first;
                } else {
                    t = rightWork.begin() -> first;
                }
            }
        }
        
        return t;
    }
};
