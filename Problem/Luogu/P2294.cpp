#include <cstdio>
#include <cstring>
#include <queue>
#include <tuple>
#include <vector>
constexpr int MaxN = 1e2 + 5;
int n, m;
int cnt[MaxN];
int dis[MaxN];
bool vis[MaxN];
std::queue<int> queue;
std::vector<std::tuple<int, int>> g[MaxN];
void solve()
{
    memset(cnt, 0, sizeof(cnt));
    memset(dis, 0, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i <= n; i++)
    {
        g[i].clear();
    }
    for (; !queue.empty();)
    {
        queue.pop();
    }
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int s, t, v;
        scanf("%d%d%d", &s, &t, &v);
        g[s - 1].push_back({t, v});
        g[t].push_back({s - 1, -v});
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
                    printf("false\n");
                    return;
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
    printf("true\n");
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