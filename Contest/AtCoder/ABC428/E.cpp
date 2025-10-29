#include <cstdio>
#include <tuple>
#include <vector>
constexpr int MaxN = 5e5 + 5;
int n;
int depth[MaxN];
int jump[21][MaxN];
std::vector<int> g[MaxN];
std::tuple<int, int> dfs(int u, int f)
{
    int a, d;
    a = u;
    d = 0;
    depth[u] = depth[f] + 1;
    jump[0][u] = f;
    for (int j = 1; j < 21; j++)
    {
        jump[j][u] = jump[j - 1][jump[j - 1][u]];
    }
    for (const auto &v : g[u])
    {
        if (v == f)
        {
            continue;
        }
        const auto &[c, f] = dfs(v, u);
        if (f > d || (f == d && c > a))
        {
            a = c;
            d = f;
        }
    }
    return {a, d + 1};
}
int lca(int u, int v)
{
    if (depth[u] < depth[v])
    {
        std::swap(u, v);
    }
    for (int j = 20; j >= 0; j--)
    {
        if (depth[jump[j][u]] >= depth[v])
        {
            u = jump[j][u];
        }
    }
    if (u == v)
    {
        return u;
    }
    for (int j = 20; j >= 0; j--)
    {
        if (jump[j][u] != jump[j][v])
        {
            u = jump[j][u];
            v = jump[j][v];
        }
    }
    return jump[0][u];
}
int distance(int u, int v)
{
    int a = lca(u, v);
    return depth[u] + depth[v] - 2 * depth[a];
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int a = std::get<0>(dfs(1, 0));
    a = std::get<0>(dfs(a, 0));
    int b = std::get<0>(dfs(a, 0));
    if (a > b)
    {
        std::swap(a, b);
    }
    for (int i = 1; i <= n; i++)
    {
        printf("%d\n", distance(a, i) > distance(b, i) ? a : b);
    }
    return 0;
}