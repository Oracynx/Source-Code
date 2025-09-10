#include <algorithm>
#include <cstdio>
#include <utility>
#include <vector>
constexpr int MaxN = 1e5 + 5;
int n, m, c;
int fa[MaxN];
int depth[MaxN];
int jump[21][MaxN];
std::vector<int> p[MaxN];
std::vector<int> g[MaxN];
std::vector<int> jumpC[21][MaxN];
void take(std::vector<int> &dist, const std::vector<int> &src)
{
    if (src.empty())
    {
        return;
    }
    size_t old = dist.size();
    size_t want = std::min<size_t>(10, old + src.size());
    if (dist.capacity() < want)
    {
        dist.reserve(want);
    }
    dist.insert(dist.end(), src.begin(), src.end());
    if (old > 0)
    {
        std::inplace_merge(dist.begin(), dist.begin() + old, dist.end());
    }
    if (dist.size() > 10)
    {
        dist.resize(10);
    }
}
void dfs(int u, int f)
{
    fa[u] = f;
    depth[u] = depth[f] + 1;
    jump[0][u] = f;
    take(jumpC[0][u], p[u]);
    for (int j = 1; j < 20; j++)
    {
        jump[j][u] = jump[j - 1][jump[j - 1][u]];
        take(jumpC[j][u], jumpC[j - 1][u]);
        take(jumpC[j][u], jumpC[j - 1][jump[j - 1][u]]);
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
std::vector<int> solve(int u, int v)
{
    std::vector<int> result;
    if (depth[u] < depth[v])
    {
        std::swap(u, v);
    }
    for (int j = 19; j >= 0; j--)
    {
        if (depth[jump[j][u]] >= depth[v])
        {
            take(result, jumpC[j][u]);
            u = jump[j][u];
        }
    }
    for (int j = 19; j >= 0; j--)
    {
        if (jump[j][u] != jump[j][v])
        {
            take(result, jumpC[j][u]);
            take(result, jumpC[j][v]);
            u = jump[j][u];
            v = jump[j][v];
        }
    }
    if (u != v)
    {
        take(result, p[u]);
        take(result, p[v]);
        u = fa[u];
        v = fa[v];
    }
    take(result, p[u]);
    return result;
}
int main()
{
    scanf("%d%d%d", &n, &m, &c);
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= m; i++)
    {
        int x;
        scanf("%d", &x);
        p[x].push_back(i);
    }
    dfs(1, 0);
    for (int i = 1; i <= c; i++)
    {
        int u, v, k;
        scanf("%d%d%d", &u, &v, &k);
        auto answer = solve(u, v);
        k = std::min(k, int(answer.size()));
        printf("%d", k);
        for (int j = 0; j < k; j++)
        {
            printf(" %d", answer[j]);
        }
        printf("\n");
    }
    return 0;
}