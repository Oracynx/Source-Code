#include <cstdio>
#include <random>
#include <tuple>
#include <vector>
std::mt19937 rnd(std::random_device{}());
constexpr int MaxN = 2e5 + 5;
int n, m;
int vis[MaxN];
long long answer;
std::vector<int> g[MaxN];
std::vector<std::tuple<int, int>> link;
int dfs(int u, int f, int flag)
{
    if (vis[u] == flag)
    {
        return 0;
    }
    vis[u] = flag;
    int result = 1;
    for (const auto &v : g[u])
    {
        if (v == f)
        {
            continue;
        }
        result += dfs(v, u, flag);
    }
    return result;
}
int main()
{
    scanf("%d%d", &n, &m);
    bool spB = true;
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        link.push_back({u, v});
        spB &= u == 1;
    }
    if (spB)
    {
        long long a, b;
        a = m / 2;
        b = m - a;
        answer = a + b + a * b + n;
        printf("%lld\n", answer);
        return 0;
    }
    printf("%lld\n", answer);
    return 0;
}