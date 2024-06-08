int dfn[maxn], low[maxn], id, st[maxn], tail = -1, from[maxn], dcc;
bool cut[maxn];
vector<int> dcc_list[maxn];
void dfs(int u, int p) {
    dfn[u] = low[u] = ++id;
    st[++tail] = u;
    int child = 0;
    for (int e = head[u]; e; e = edges[e].nxt) {
        int to = edges[e].to;
        if (to == p) continue;
        if (dfn[to]) {
            low[u] = min(low[u], dfn[to]);
        } else {
            child++;
            dfs(to, u);
            low[u] = min(low[u], low[to]);
            if (low[to] >= dfn[u]) {
                from[to] = ++dcc;
                while (st[tail] != to) {  // 注意是 pop 到 to 为止（包括to）
                    int cur = st[tail--];
                    from[cur] = from[to];
                    dcc_list[dcc].push_back(cur);
                }
                tail--;  // tail--后，指向的是 u
                dcc_list[dcc].push_back(to);
                dcc_list[dcc].push_back(u);  // 注意 u是割点，也要进入该分量
                // from[u] = dcc;  // from[u] 实际上没有意义
            }
            if (low[to] >= dfn[u] && p) cut[u] = 1;  // 割点（非根节点）
        }
    }
    if (!p && child >= 2) cut[u] = 1;  // 割点（根节点）
}
void tarjan() {
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) dfs(i, 0);
    }
}
void rebuild() {
    for (int i = 1; i <= dcc; i++) {
        for (int j : dcc_list[i]) {
            if (cut[j]) cut_from[j].push_back(i);
        }
    }
    for (int u = 1; u <= n; u++) {
        if (cut[u]) {
            int fu = from[u] = ++dcc;
            mp[dcc] = u;
            dcc_list[dcc].push_back(u);
            for (int fv : cut_from[u]) {
                adj[fu].push_back(fv);
                adj[fv].push_back(fu);
            }
        }
    }
}
