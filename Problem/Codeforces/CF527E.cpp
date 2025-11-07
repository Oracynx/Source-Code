#include <cstdio>
#include <tuple>
#include <vector>
constexpr int MaxN = 1e5 + 5;
constexpr int MaxM = 5e5 + 5;
int n, m;
bool vis[MaxM];
std::vector<int> odd;
std::vector<std::tuple<int, int>> g[MaxN];
std::vector<std::tuple<int, int>>::iterator cur[MaxN];
void add(int u, int v)
{
    static int index = 0;
    g[u].push_back({v, ++index});
    g[v].push_back({u, index});
}
bool cross(int w)
{
    if (vis[w])
    {
        return false;
    }
    vis[w] = true;
    return true;
}
void dfs(int u)
{
    static bool sta = true;
    for (auto &it = cur[u]; it != g[u].end();)
    {
        const auto &[v, w] = *it++;
        if (cross(w))
        {
            dfs(v);
            printf("%d %d\n", sta ? u : v, sta ? v : u);
            sta ^= true;
        }
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
    }
    for (int i = 1; i <= n; i++)
    {
        if (int(g[i].size()) % 2 == 1)
        {
            odd.push_back(i);
        }
    }
    for (int i = 0; i < int(odd.size()); i += 2)
    {
        m++;
        add(odd[i], odd[i + 1]);
    }
    if (m % 2 == 1)
    {
        m++;
        add(1, 1);
    }
    for (int i = 1; i <= n; i++)
    {
        cur[i] = g[i].begin();
    }
    printf("%d\n", m);
    dfs(1);
    return 0;
}