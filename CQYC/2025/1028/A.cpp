#include <cstdio>
#include <vector>
constexpr int MaxN = 5e5 + 5;
int n;
int answer;
bool vis[MaxN];
std::vector<int> g[MaxN];
bool dfs(int u, int f)
{
    if (vis[u])
    {
        return true;
    }
    vis[u] = true;
    for (const auto &v : g[u])
    {
        if (v == f)
        {
            continue;
        }
        if (dfs(v, u))
        {
            return true;
        }
    }
    return false;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    answer = 2 * n;
    for (int i = 1; i <= 2 * n; i++)
    {
        if (vis[i])
        {
            continue;
        }
        answer -= dfs(i, 0) ? 0 : 1;
    }
    printf("%d\n", answer);
    return 0;
}