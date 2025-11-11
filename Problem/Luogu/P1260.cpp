#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <tuple>
#include <vector>
constexpr int MaxN = 1e3 + 5;
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
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g[v].push_back({u, w});
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
                    printf("NO SOLUTION\n");
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
    int ad = *std::min_element(dis + 1, dis + 1 + n);
    for (int i = 1; i <= n; i++)
    {
        printf("%d\n", dis[i] - ad);
    }
    return 0;
}