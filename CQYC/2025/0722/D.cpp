#include <cstdio>
#include <utility>
#include <vector>
constexpr int MaxN = 2e5 + 5;
int n;
int depth[MaxN];
int jump[21][MaxN];
long long p[MaxN];
long long answer[MaxN];
std::vector<int> g[MaxN];
long long gcd(long long x, long long y)
{
    for (;;)
    {
        if (x < y)
        {
            std::swap(x, y);
        }
        if (y == 0)
        {
            return x;
        }
        x %= y;
    }
}
void dfsInit(int u, int f)
{
    jump[0][u] = f;
    depth[u] = depth[f] + 1;
    for (int j = 1; j < 20; j++)
    {
        jump[j][u] = jump[j - 1][jump[j - 1][u]];
    }
    for (const auto &v : g[u])
    {
        if (v == f)
        {
            continue;
        }
        dfsInit(v, u);
    }
}
int lca(int x, int y)
{
    if (depth[x] < depth[y])
    {
        std::swap(x, y);
    }
    for (int j = 19; j >= 0; j--)
    {
        if (depth[jump[j][x]] > depth[y])
        {
            x = jump[j][x];
        }
    }
    if (depth[x] > depth[y])
    {
        x = jump[0][x];
    }
    for (int j = 19; j >= 0; j--)
    {
        if (jump[j][x] != jump[j][y])
        {
            x = jump[j][x];
            y = jump[j][y];
        }
    }
    if (x != y)
    {
        x = jump[0][x];
    }
    return x;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &p[i]);
    }
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfsInit(1, 1);
    return 0;
}