#include <cstdio>
#include <map>
#include <numeric>
#include <tuple>
#include <vector>
constexpr int MaxN = 5e5 + 5;
int n, m;
int p[MaxN];
int fd[MaxN];
int ref[MaxN];
int vis[MaxN];
std::vector<int> og[MaxN];
std::vector<int> g[MaxN];
std::map<std::tuple<int, int>, bool> map;
int find(int u)
{
    return fd[u] == u ? u : fd[u] = find(fd[u]);
}
void merge(int u, int v)
{
    u = find(u);
    v = find(v);
    fd[v] = u != v ? u : fd[v];
}
std::tuple<int, int> dfs(int u, int l)
{
    if (vis[u] == l)
    {
        return {0, -0x3f3f3f3f'3f3f3f3f};
    }
    vis[u] = l;
    int r, d;
    r = u;
    d = 0;
    for (const auto &v : g[u])
    {
        if (vis[v] == l)
        {
            continue;
        }
        const auto &[cr, cd] = dfs(v, l);
        if (cd + 1 > d)
        {
            r = cr;
            d = cd + 1;
        }
    }
    return {r, d};
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }
    std::iota(fd + 1, fd + 1 + n, 1);
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        og[u].push_back(v);
        og[v].push_back(u);
        if (p[u] == p[v])
        {
            merge(u, v);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (ref[find(i)] == 0)
        {
            ref[find(i)] = ++m;
        }
    }
    for (int ou = 1; ou <= n; ou++)
    {
        for (const auto &ov : og[ou])
        {
            int u = ref[find(ou)];
            int v = ref[find(ov)];
            if (u == v)
            {
                continue;
            }
            g[u].push_back(v);
        }
    }
    const auto &[r, d] = dfs(std::get<0>(dfs(1, 1)), 2);
    printf("%d\n", (d + 1) / 2);
    return 0;
}