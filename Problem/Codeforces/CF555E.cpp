#include <cstdio>
#include <cstring>
#include <map>
#include <numeric>
#include <tuple>
#include <unordered_set>
#include <vector>
constexpr int MaxN = 2e5 + 5;
int n, m, c;
int fi[MaxN];
int fa[MaxN];
int tfa[MaxN];
int depth[MaxN];
int jump[21][MaxN];
int ad[MaxN][2];
bool vis[MaxN];
std::vector<int> g[MaxN];
std::vector<int> ng[MaxN];
std::map<std::tuple<int, int>, bool> map;
int find(int u)
{
    return fi[u] == u ? u : fi[u] = find(fi[u]);
}
void merge(int u, int v)
{
    int fu, fv;
    fu = find(u);
    fv = find(v);
    if (fu != fv)
    {
        fi[fv] = fu;
    }
}
int tfind(int u)
{
    return tfa[u] == u ? u : tfa[u] = tfind(tfa[u]);
}
void tmerge(int u, int v)
{
    int fu, fv;
    fu = tfind(u);
    fv = tfind(v);
    if (fu != fv)
    {
        if (depth[u] > depth[v])
        {
            std::swap(u, v);
        }
        tfa[v] = u;
    }
}
void tarjan(int u, int f)
{
    depth[u] = depth[f] + 1;
    for (const auto &v : g[u])
    {
        if (v == f)
        {
            f = 0;
            continue;
        }
        if (depth[v] == 0)
        {
            tarjan(v, u);
        }
        int fu, fv;
        fu = tfind(u);
        fv = tfind(v);
        if (depth[fv] >= 1)
        {
            tmerge(fu, fv);
        }
    }
    depth[u] = -1;
}
void mkjump(int u, int f)
{
    vis[u] = true;
    jump[0][u] = f;
    depth[u] = depth[f] + 1;
    for (int j = 1; j < 21; j++)
    {
        jump[j][u] = jump[j - 1][jump[j - 1][u]];
    }
    for (const auto &v : ng[u])
    {
        if (v == f)
        {
            continue;
        }
        mkjump(v, u);
    }
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
    for (int j = 20; j >= 0; j--)
    {
        if (jump[j][u] != jump[j][v])
        {
            u = jump[j][u];
            v = jump[j][v];
        }
    }
    if (u != v)
    {
        u = jump[0][u];
    }
    return u;
}
std::tuple<bool, int, int> check(int u, int f, bool &suc)
{
    vis[u] = true;
    int sa, sb;
    sa = sb = 0;
    for (const auto &v : ng[u])
    {
        if (v == f)
        {
            continue;
        }
        const auto &[_suc, ca, cb] = check(v, u, suc);
        sa += ca;
        sb += cb;
    }
    sa += ad[u][0];
    sb += ad[u][1];
    if (sa != 0 && sb != 0)
    {
        suc = false;
    }
    return {suc, sa, sb};
}
int main()
{
    scanf("%d%d%d", &n, &m, &c);
    std::iota(fi + 1, fi + 1 + n, 1);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
        merge(u, v);
    }
    std::iota(tfa + 1, tfa + 1 + n, 1);
    for (int i = 1; i <= n; i++)
    {
        if (depth[i] == 0)
        {
            tarjan(i, 0);
        }
    }
    for (int u = 1; u <= n; u++)
    {
        for (const auto &v : g[u])
        {
            int fu, fv;
            fu = tfind(u);
            fv = tfind(v);
            if (map[{fu, fv}] || fu == fv)
            {
                continue;
            }
            ng[fu].push_back(fv);
            ng[fv].push_back(fu);
            map[{fu, fv}] = true;
            map[{fv, fu}] = true;
        }
    }
    std::unordered_set<int> set;
    for (int i = 1; i <= n; i++)
    {
        set.insert(tfind(i));
    }
    n = set.size();
    memset(depth, 0, sizeof(depth));
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            mkjump(i, 0);
        }
    }
    for (int i = 1; i <= c; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        if (find(u) != find(v))
        {
            printf("No\n");
            return 0;
        }
        u = tfind(u);
        v = tfind(v);
        int ca = lca(u, v);
        ad[ca][0]--;
        ad[ca][1]--;
        ad[u][0]++;
        ad[v][1]++;
    }
    memset(vis, 0, sizeof(vis));
    bool suc = true;
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            check(i, 0, suc);
        }
    }
    printf("%s\n", suc ? "Yes" : "No");
    return 0;
}