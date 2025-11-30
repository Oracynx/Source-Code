#include <cstdio>
#include <utility>
#include <vector>
constexpr int MaxN = 5e5 + 5;
int n, m, s;
int dep[MaxN];
int jump[MaxN][21];
std::vector<int> g[MaxN];
void dfs(int u, int f)
{
    dep[u] = dep[f] + 1;
    jump[u][0] = f;
    for (int j = 1; j < 21; j++)
    {
        jump[u][j] = jump[jump[u][j - 1]][j - 1];
    }
    for (const auto &v : g[u])
    {
        if (v == f)
        {
            continue;
        }
        dfs(v, u);
    }
}
int LCA(int u, int v)
{
    if (dep[u] < dep[v])
    {
        std::swap(u, v);
    }
    for (int j = 20; j >= 0; j--)
    {
        if (dep[jump[u][j]] >= dep[v])
        {
            u = jump[u][j];
        }
    }
    for (int j = 20; j >= 0; j--)
    {
        if (jump[u][j] != jump[v][j])
        {
            u = jump[u][j];
            v = jump[v][j];
        }
    }
    return u == v ? u : jump[u][0];
}
int main()
{
    scanf("%d%d%d", &n, &m, &s);
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(s, 0);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%d\n", LCA(u, v));
    }
    return 0;
}