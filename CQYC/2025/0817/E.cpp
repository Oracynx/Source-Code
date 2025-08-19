#include <cstdio>
#include <vector>
constexpr int MaxN = 1e6 + 5;
int n, m;
int p[MaxN];
int fa[MaxN];
std::vector<int> g[MaxN];
void dfsInit(int u, int f)
{
    fa[u] = f;
    for (const auto &v : g[u])
    {
        if (v == f)
        {
            continue;
        }
        dfsInit(v, u);
    }
}
long long dfs(int u, int f, int len, int limit)
{
    long long result = p[u] ^ len;
    if (len == limit)
    {
        return result;
    }
    for (const auto &v : g[u])
    {
        if (v == f)
        {
            continue;
        }
        result += dfs(v, u, len + 1, limit);
    }
    return result;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfsInit(1, 0);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
        int x, k;
        scanf("%d%d", &x, &k);
        printf("%lld\n", dfs(x, fa[x], 0, k));
    }
    return 0;
}