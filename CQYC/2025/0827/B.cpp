#include <cstdio>
#include <cstring>
#include <queue>
#include <tuple>
#include <vector>
constexpr int MaxN = 2e5 + 5;
int n, m;
int p[MaxN];
bool vis[MaxN];
long long dis[MaxN];
std::vector<std::tuple<int, int>> g[MaxN];
std::priority_queue<std::tuple<long long, int>> queue;
void solve()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n + 1; i++)
    {
        vis[i] = false;
        dis[i] = 0x3f3f3f3f'3f3f3f3f;
        g[i].clear();
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
        g[i].push_back({i + 1, p[i]});
        g[i + 1].push_back({i, p[i]});
    }
    for (int i = 1; i <= m; i++)
    {
        int l, r, c;
        scanf("%d%d%d", &l, &r, &c);
        g[l].push_back({r + 1, c});
        g[r + 1].push_back({l, c});
    }
    dis[1] = 0;
    queue.push({0, 1});
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
    long long answer = -dis[n + 1];
    for (int i = 1; i <= n; i++)
    {
        answer += p[i];
    }
    printf("%lld\n", answer);
}
int main()
{
    int c, t;
    scanf("%d%d", &c, &t);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}