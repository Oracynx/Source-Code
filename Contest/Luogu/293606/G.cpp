#include <algorithm>
#include <cstdio>
#include <queue>
#include <tuple>
#include <vector>
constexpr int MaxN = 1e5 + 5;
int n, m, s;
bool vis[MaxN];
long long dis[MaxN];
std::vector<std::tuple<int, int>> g[MaxN];
std::priority_queue<std::tuple<int, int>> queue;
int main()
{
    scanf("%d%d%d", &n, &m, &s);
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g[u].push_back({v, w});
    }
    std::fill(dis + 1, dis + 1 + n, 0x3f3f3f3f'3f3f3f3f);
    dis[s] = 0;
    queue.push({0, s});
    for (; !queue.empty();)
    {
        const auto [d, u] = queue.top();
        queue.pop();
        if (vis[u])
        {
            continue;
        }
        vis[u] = true;
        for (const auto &[v, w] : g[u])
        {
            if (dis[u] + w < dis[v])
            {
                dis[v] = dis[u] + w;
                queue.push({-dis[v], v});
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        printf("%lld ", dis[i]);
    }
    printf("\n");
    return 0;
}