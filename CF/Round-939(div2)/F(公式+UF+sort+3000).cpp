#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector

const int N = 2e6 + 10;
int L[N], R[N];
int p[N], pos[N];
int find(int u) {
  return p[u] == u ? u : p[u] = find(p[u]);
}

//i <= j
//i + L[i] <= j - L[j]
//i + R[i] >= j - R[j]

struct Segment {
  int l, r, i;
  bool operator<(const Segment& other) {
    return l < other.l;
  }
};

class Compare {
public:
    bool operator()(Segment& a, Segment& b)
    {
       return a.r < b.r;
    }
};


void solve() {
  int n;
  scanf("%d", &n);
  for(int i = 1; i <= n; i++) {
    scanf("%d%d", &L[i], &R[i]);
  }

  //[i + L[i], i + R[i]] intersect with [j - R[j], j - L[j]]
  vector<int> line1(3 * n + 4), line2(3 * n + 4);
  vector<Segment> left, right;
  for(int i = 1; i <= n; i++) {
    int l1 = i + L[i], r1 = i + R[i];
    int l2 = i - R[i], r2 = i - L[i];
    l1 += n;
    r1 += n;
    l2 += n;
    r2 += n;
    line1[l1]++; line1[r1 + 1]--;
    line2[l2]++; line2[r2 + 1]--;
    right.push_back({l1, r1, i});
    left.push_back({l2, r2, i});
    //cout << i << "  left " << l2 << " " << r2 << endl;
    //cout << i << "  right " << l1 << " " << r1 << endl;
  }

  for(int i = 1; i < line1.size(); i++) {
    line1[i] += line1[i - 1];
    line2[i] += line2[i - 1];
  }

  sort(left.begin(), left.end());
  sort(right.begin(), right.end());
  for(int i = 0; i <= n; i++) p[i] = i;

  priority_queue<Segment, vector<Segment>, Compare> rpq, lpq;
  int index1 = 0, index2 = 0;
  for(int i = 0; i < line1.size(); i++) {
    if(line1[i] == 0 || line2[i] == 0) continue;
    while(index1 < right.size() && right[index1].l <= i) {
      rpq.push(right[index1]);
      index1++;
    }
    while(index2 < left.size() && left[index2].l <= i) {
      lpq.push(left[index2]);
      index2++;
    }

    if(rpq.size() > 0 && rpq.top().r >= i && lpq.size() > 0 && lpq.top().r >= i) {
      int pi = 0;
      int l = rpq.top().l, r = rpq.top().r, idx = rpq.top().i;
      while(rpq.size() > 0 && rpq.top().r >= i) {
        Segment seg = rpq.top(); rpq.pop();
        l = min(l, seg.l); r = max(r, seg.r);
        pos[pi++] = seg.i;
      }
      rpq.push({l, r, idx});
      
      
      l = lpq.top().l; r = lpq.top().r; idx = lpq.top().i;
      while(lpq.size() > 0 && lpq.top().r >= i) {
        Segment seg = lpq.top(); lpq.pop();
        l = min(l, seg.l); r = max(r, seg.r);
        pos[pi++] = seg.i;
      }
      lpq.push({l, r, idx});

      for(int j = 1; j < pi; j++) {
        int r1 = find(pos[j - 1]), r2 = find(pos[j]);
        if(r1 != r2) p[r1] = r2;
      }
    }
  }
  
  set<int> s;
  for(int i = 1; i <= n; i++) {
    s.insert(find(i));
  }
  printf("%d\n", (int)(s.size()));
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
