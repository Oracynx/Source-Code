#include <cstdio>
#include <queue>
#include <tuple>
#include <vector>
constexpr int MaxN = 5e3 + 5;
int n, m;
int dis[MaxN];
int cnt[MaxN];
bool vis[MaxN];
std::queue<int> queue;
std::vector<std::tuple<int, int>> g[MaxN];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int op;
        scanf("%d", &op);
        if (op == 1)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            g[u].push_back({v, -w});
        }
        else if (op == 2)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            g[v].push_back({u, w});
        }
        else
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g[u].push_back({v, 0});
            g[v].push_back({u, 0});
        }
    }
    for (int i = 1; i <= n; i++)
    {
        queue.push(i);
    }
    for (; !queue.empty();)
    {
        int u = queue.front();
        queue.pop();
        vis[u] = false;
        for (const auto &[v, w] : g[u])
        {
            if (dis[u] + w < dis[v])
            {
                cnt[v]++;
                if (cnt[v] > n)
                {
                    printf("No\n");
                    return 0;
                }
                dis[v] = dis[u] + w;
                if (!vis[v])
                {
                    queue.push(v);
                }
                vis[v] = true;
            }
        }
    }
    printf("Yes\n");
    return 0;
}