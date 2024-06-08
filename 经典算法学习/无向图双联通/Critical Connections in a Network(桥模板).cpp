//https://tom0727.github.io/post/041-%E5%89%B2%E7%82%B9-%E6%A1%A5-bcc/
//https://oi-wiki.org/graph/cut/

//求边的双联通，只需要把桥全删掉，再找连通块就可以
namespace Bridge {
  const int N = 1e5 + 10;
  int dfn[N], low[N], t = 0;
  vector<int> g[N];
  vector<int> ans;
  vector<vector<int>> bridge;

  void init(int n) {
    t = 0;
    for(int i = 0; i <= n; i++) {
      dfn[i] = low[i] = 0;
      g[i].clear();
    }
    bridge.clear();
  }

  void add(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
  }

  void tarjan(int pa, int u) {
    low[u] = dfn[u] = ++t;
    for(int to : g[u]) {
      if(to == pa) continue;
      if(dfn[to]) {
        low[u] = min(low[u], dfn[to]);
      } else {
        tarjan(u, to);
        low[u] = min(low[u], low[to]);
        if(low[to] > dfn[u]) { //bridge
            bridge.push_back({u, to});
        }
      }
    }
  }
}

class Solution {
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        Bridge :: init(n);
        for(auto& e : connections) {
            int u = e[0], v = e[1];
            Bridge :: add(u, v);
        }
        
        for(int i = 0; i < n; i++) {
            if(!Bridge :: dfn[i]) {
                Bridge :: tarjan(-1, i);
            }
        }
        
        return Bridge :: bridge;
    }
};
