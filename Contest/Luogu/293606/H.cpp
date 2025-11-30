#include <algorithm>
#include <cstdio>
#include <queue>
#include <tuple>
#include <vector>
constexpr int MaxN = 2e3 + 5;
int n, m;
int dis[MaxN];
int deg[MaxN];
bool vis[MaxN];
std::queue<int> queue;
std::vector<std::tuple<int, int>> g[MaxN];
int solve()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        g[i].clear();
    }
    for (; !queue.empty();)
    {
        queue.pop();
    }
    std::fill(deg + 1, deg + 1 + n, 0);
    std::fill(vis + 1, vis + 1 + n, false);
    std::fill(dis + 1, dis + 1 + n, 0x3f3f3f3f);
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        if (w >= 0)
        {
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }
        else
        {
            g[u].push_back({v, w});
        }
    }
    dis[1] = 0;
    queue.push(1);
    for (; !queue.empty();)
    {
        int u = queue.front();
        queue.pop();
        vis[u] = false;
        for (const auto &[v, w] : g[u])
        {
            if (dis[u] + w < dis[v])
            {
                deg[v]++;
                if (deg[v] > n)
                {
                    printf("YES\n");
                    return 0;
                }
                dis[v] = dis[u] + w;
                if (!vis[v])
                {
                    vis[v] = true;
                    queue.push(v);
                }
            }
        }
    }
    printf("NO\n");
    return 0;
}
int main()
{
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}