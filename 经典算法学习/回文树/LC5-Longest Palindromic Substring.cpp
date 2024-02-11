const int N = 1000 + 100;
struct PalindromeTree {
    char s[N];
    int len[N], fail[N], ch[N][256], cnt[N];
    int tot = 0, last = 0;    
    
    void init() {
        memset(cnt, 0, sizeof cnt);
        memset(ch, 0, sizeof ch);
        s[0] = -1;
        len[0] = 0; //初始化even root 
        len[1] = -1;//初始化odd root 
        fail[0] = 1;
        fail[1] = 1;
        tot = 1;
        last = 0;
    }
    
    int getfail(int x, int i) { //寻找fail node
        while(s[i - len[x] - 1] != s[i]) x = fail[x];
        return x;
    }
    
    int newnode(int x) { //简历长度为x 的新node
        tot++;
        len[tot] = x;
        return tot;
    }

    
    void add(int i) {
        int failnode = getfail(last, i);
        if(ch[failnode][s[i]] == 0) { //需要新建node
            int node = newnode(len[failnode] + 2); //前后都加上新字符，所以新回文串长度要加2
            fail[node] = ch[getfail(fail[failnode], i)][s[i]]; //因为fail指向的是原串的严格后缀，所以要从failnode的fail开始找起 
            ch[failnode][s[i]] = node;
        }
        last = ch[failnode][s[i]];
        cnt[last]++;
    }
} pt1;

class Solution {
public:
    string longestPalindrome(string s) {
        pt1.init();
        int ans = 0, r = -1;
        for(int i = 0; i < s.size(); i++) {
            pt1.s[i + 1] = s[i];
            pt1.add(i + 1);
            if(pt1.len[pt1.last] > ans) {
                ans = pt1.len[pt1.last];
                r = i + 1;
            }
        }
        return s.substr(r - ans, ans);
    }
};
