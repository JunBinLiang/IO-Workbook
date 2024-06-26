//https://www.acwing.com/problem/content/description/370/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int N = 100010, M = 600010;

int n, m;
int h[N], hs[N], e[M], ne[M], w[M], idx;
int dfn[N], low[N], timestamp;
int stk[N], top;
bool in_stk[N];
int id[N], scc_cnt, sz[N];
int dist[N];

void add(int h[], int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ timestamp;
    stk[ ++ top] = u, in_stk[u] = true;

    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        }
        else if (in_stk[j]) low[u] = min(low[u], low[j]);
    }

    if (dfn[u] == low[u])
    {
        ++ scc_cnt;
        int y;
        do {
            y = stk[top -- ];
            in_stk[y] = false;
            id[y] = scc_cnt;
            sz[scc_cnt] ++ ;
        } while (y != u);
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);
    memset(hs, -1, sizeof hs);

    for (int i = 1; i <= n; i ++ ) add(h, 0, i, 1);

    while (m -- )
    {
        int t, a, b;
        scanf("%d%d%d", &t, &a, &b);
        if (t == 1) add(h, b, a, 0), add(h, a, b, 0);
        else if (t == 2) add(h, a, b, 1);
        else if (t == 3) add(h, b, a, 0);
        else if (t == 4) add(h, b, a, 1);
        else add(h, a, b, 0);
    }

    tarjan(0);

    bool success = true;
    for (int i = 0; i <= n; i ++ )
    {
        for (int j = h[i]; ~j; j = ne[j])
        {
            int k = e[j];
            int a = id[i], b = id[k];
            if (a == b)
            {
                if (w[j] > 0)
                {
                    success = false;
                    break;
                }
            }
            else add(hs, a, b, w[j]);
        }
        if (!success) break;
    }

    if (!success) puts("-1");
    else
    {   
        //topo
        for (int i = scc_cnt; i; i -- )
        {
            for (int j = hs[i]; ~j; j = ne[j])
            {
                int k = e[j];
                dist[k] = max(dist[k], dist[i] + w[j]);
            }
        }

        LL res = 0;
        for (int i = 1; i <= scc_cnt; i ++ ) res += (LL)dist[i] * sz[i];

        printf("%lld\n", res);
    }

    return 0;
}
