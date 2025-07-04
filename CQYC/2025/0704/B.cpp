#include <algorithm>
#include <cstdio>
#include <vector>
constexpr int MaxN = 2e3 + 5;
int n, m, q, type;
int vis[MaxN];
std::vector<int> g[MaxN];
int dfs(int u, int dep, int t, int k, int flag1, int flag2)
{
    if (vis[u] == flag1)
    {
        return -2;
    }
    if (vis[u] == flag2)
    {
        return -1;
    }
    if (u == t)
    {
        return dep == k ? u : 0;
    }
    vis[u] = flag1;
    for (const auto &v : g[u])
    {
        int r = dfs(v, dep + 1, t, k, flag1, flag2);
        if (r == -1)
        {
            continue;
        }
        vis[u] = 0;
        if (r == -2)
        {
            return -2;
        }
        if (r == 0 && dep == k)
        {
            return u;
        }
        return r;
    }
    vis[u] = flag2;
    return -1;
}
int main()
{
    freopen("path.in", "r", stdin);
    freopen("path.out", "w", stdout);
    scanf("%d%d%d%d", &n, &m, &q, &type);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
    }
    for (int i = 1; i <= n; i++)
    {
        std::sort(g[i].begin(), g[i].end());
    }
    int lastAnswer = 1;
    for (int i = 1; i <= q; i++)
    {
        int s, t, k;
        scanf("%d%d%d", &s, &t, &k);
        if (type == 1)
        {
            s = (s ^ lastAnswer) % n + 1;
            t = (t ^ lastAnswer) % n + 1;
            k = (k ^ lastAnswer) % n + 1;
        }
        int r = dfs(s, 1, t, k, 2 * i - 1, 2 * i);
        if (r <= 0)
        {
            printf("-1\n");
            lastAnswer = 1;
        }
        else
        {
            printf("%d\n", lastAnswer = r);
        }
    }
    return 0;
}