#include <algorithm>
#include <cstdio>
#include <functional>
#include <tuple>
#include <vector>
constexpr int MaxN = 2e6 + 5;
int n;
int answer;
int p[MaxN];
int fa[MaxN];
bool vis[MaxN];
std::vector<int> g[MaxN];
std::vector<std::tuple<int, int>> v;
void dfs(int u, int f, int d)
{
    v.push_back({d, u});
    fa[u] = f;
    for (const auto &v : g[u])
    {
        if (v == f)
        {
            continue;
        }
        dfs(v, u, d + 1);
    }
}
int main()
{
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    scanf("%*d");
    scanf("%d", &n);
    n *= 2;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vis[0] = true;
    dfs(1, 0, 1);
    std::sort(v.begin(), v.end(), std::greater<>());
    for (const auto &[_a, u] : v)
    {
        if (!vis[u] && !vis[fa[u]])
        {
            answer++;
            vis[u] = true;
            vis[fa[u]] = true;
        }
    }
    printf("%d %d\n", answer, 0);
    return 0;
}