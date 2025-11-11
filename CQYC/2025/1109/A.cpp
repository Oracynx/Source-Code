#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>
#include <tuple>
#include <vector>
constexpr int MaxN = 1e6 + 6;
int n, m;
int dis[MaxN];
std::deque<std::tuple<int, int>> queue;
std::vector<std::tuple<int, int>> g[MaxN];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        if ((r - l + 1) % 2 != 0)
        {
            printf("-1\n");
            return 0;
        }
        g[l - 1].push_back({r, 0});
        g[r].push_back({l - 1, 0});
    }
    for (int i = 1; i <= n; i++)
    {
        g[i - 1].push_back({i, 1});
        g[i].push_back({i - 1, 1});
    }
    std::fill(dis + 1, dis + 1 + n, 0x3f3f3f3f);
    queue.push_back({0, 0});
    for (; !queue.empty();)
    {
        const auto [d, u] = queue.front();
        queue.pop_front();
        if (dis[u] != d)
        {
            continue;
        }
        for (const auto &[v, w] : g[u])
        {
            if (dis[u] + w < dis[v])
            {
                dis[v] = dis[u] + w;
                if (w == 0)
                {
                    queue.push_front({dis[v], v});
                }
                else
                {
                    queue.push_back({dis[v], v});
                }
            }
        }
        printf("%d %d\n", u, d);
    }
    for (int i = 1; i <= n; i++)
    {
        int d = dis[i] - dis[i - 1];
        printf("%d", d == 1 ? 0 : 1);
    }
    printf("\n");
    return 0;
}