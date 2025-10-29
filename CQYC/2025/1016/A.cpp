#include <cstdio>
#include <queue>
#include <tuple>
#include <vector>
constexpr int MaxN = 5e3 + 5;
int n, m;
int answer;
bool vis[MaxN][MaxN];
bool suc[MaxN][MaxN];
std::vector<int> g[MaxN][26];
std::vector<int> rg[MaxN][26];
std::queue<std::tuple<int, int>> queue;
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        char w;
        scanf("%d%d", &u, &v);
        scanf(" %c", &w);
        g[u][w - 'a'].push_back(v);
        rg[v][w - 'a'].push_back(u);
    }
    for (int u = 1; u <= n; u++)
    {
        queue.push({u, u});
        for (int c = 0; c < 26; c++)
        {
            for (const auto &v : g[u][c])
            {
                queue.push({u, v});
            }
        }
    }
    for (; !queue.empty();)
    {
        const auto [s, t] = queue.front();
        queue.pop();
        if (vis[s][t])
        {
            continue;
        }
        vis[s][t] = true;
        for (int c = 0; c < 26; c++)
        {
            for (const auto &u : rg[s][c])
            {
                for (const auto &v : g[t][c])
                {
                    if (!vis[u][v])
                    {
                        queue.push({u, v});
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            answer += i != j && vis[i][j] ? 1 : 0;
        }
    }
    printf("%d\n", answer);
    return 0;
}