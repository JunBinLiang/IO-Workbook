#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector



const int N = 5e5 + 10;
char ans[N];

//linkedlist
int nxt[N], pre[N];
char val[N];
int head = 0, tail = 1;
int id = 2;


void add(int pnode, int node) {
  int nxtnode = nxt[pnode];
  nxt[node] = nxtnode;
  pre[nxtnode] = node;
  pre[node] = pnode;
  nxt[pnode] = node;
}

void addtail(int node) {
  int pnode = pre[tail];
  nxt[pnode] = node;
  pre[node] = pnode;
  pre[tail] = node;
  nxt[node] = tail;
}

void solve() {
  string s;
  cin >> s;
  int n = s.size();

  vector<int> pos(n + 1, -1);
  int j = 1;
  for(int i = 0; i < n; i++) {
    if(s[i] == ')') {
      pos[j++] = i;
    } 
  }
  //boundary
  pos[n / 2 + 1] = n;
  
  vector<int> group(n, 0);
  int count = pos[1];
  int p = 1;
  while(p <= n / 2) {
    int l = pos[p], r = pos[p + count] - 1;
    for(int i = l; i <= r; i++) {
      group[i] = 1 + group[l - 1];
    }
    p += count;
    count = (r - l + 1 - count);
  }
  
  memset(nxt, -1, sizeof nxt);
  memset(pre, -1, sizeof pre);
  nxt[head] = tail;
  pre[tail] = head;
  queue<int> lastq;
  for(int i = 0; i < n; i++) {
    int j = i;
    queue<int> curq;
    int pnode = -1;
    while(j < n && group[i] == group[j]) {
      int newnode = id++;
      val[newnode] = s[j];
      if(group[j] == 0) {
        add(head, newnode);
        curq.push(newnode);
        j++;
        continue;
      }
      if(s[j] == '(') {
        add(pnode, newnode);
        curq.push(newnode);
      } else {
        pnode = lastq.front(); lastq.pop();
        add(pnode, newnode);
      }
      j++;
    }
    
    /*int cur = nxt[head];
    while(cur != tail) {
     cout << val[cur];
     cur = nxt[cur];
    }  cout << endl;*/
    lastq = curq;
    i = j - 1;
  }

  int cur = nxt[head];
  while(cur != tail) {
    cout << val[cur];
    cur = nxt[cur];
  }

}

//((( )()) )  -> ()()(())
//( ) ( ) ( ( ))

int main(){
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
