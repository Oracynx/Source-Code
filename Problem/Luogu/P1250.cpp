#include <cstdio>
#include <cstring>
#include <queue>
#include <tuple>
#include <vector>
constexpr int MaxN = 3e4 + 5;
int n, m;
int answer;
int dis[MaxN];
bool vis[MaxN];
std::queue<int> queue;
std::vector<std::tuple<int, int>> g[MaxN];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        g[i - 1].push_back({i, 1});
        g[i].push_back({i - 1, 0});
    }
    for (int i = 1; i <= m; i++)
    {
        int l, r, d;
        scanf("%d%d%d", &l, &r, &d);
        g[r].push_back({l - 1, -d});
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
                dis[v] = dis[u] + w;
                if (!vis[v])
                {
                    queue.push(v);
                }
                vis[v] = true;
            }
        }
    }
    printf("%d\n", dis[n] - dis[0]);
    return 0;
}