#include <cstdio>
#include <cstring>
#include <queue>
#include <tuple>
#include <vector>
constexpr int MaxN = 2e5 + 5;
int n, m;
bool full[MaxN];
char status[MaxN];
std::vector<int> g[MaxN];
std::tuple<int, int> ad[MaxN][2];
std::queue<std::tuple<int, int, int>> queue;
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    scanf("%s", status + 1);
    for (int i = 1; i <= n; i++)
    {
        if (status[i] == 'S')
        {
            queue.push({i, 0, i});
        }
    }
    for (int i = 1; i <= n; i++)
    {
        ad[i][0] = {0x3f3f3f3f, 0};
        ad[i][1] = {0x3f3f3f3f, 0};
    }
    for (; !queue.empty();)
    {
        auto [u, d, f] = queue.front();
        queue.pop();
        if (f != std::get<1>(ad[u][0]) && f != std::get<1>(ad[u][1]))
        {
            if (d < std::get<0>(ad[u][0]))
            {
                ad[u][1] = ad[u][0];
                ad[u][0] = {d, f};
            }
            else if (d < std::get<0>(ad[u][1]))
            {
                ad[u][1] = {d, f};
            }
            else
            {
                continue;
            }
        }
        else
        {
            continue;
        }
        if (ad[u][0] != std::tuple<int, int>{0x3f3f3f3f, 0} && ad[u][1] != std::tuple<int, int>{0x3f3f3f3f, 0})
        {
            full[u] = true;
        }
        for (int v : g[u])
        {
            if (!full[v])
            {
                queue.push({v, d + 1, f});
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (status[i] == 'D')
        {
            printf("%d\n", std::get<0>(ad[i][0]) + std::get<0>(ad[i][1]));
        }
    }
    return 0;
}