#include <cstdio>
#include <vector>
constexpr int MaxN = 1e6 + 5;
constexpr long long Mod = 998'244'353;
int n;
int fa[MaxN];
int up[MaxN];
int size[MaxN];
long long answer;
std::vector<int> g[MaxN];
long long fsp(long long x, long long y)
{
    long long result = 1;
    for (; y != 0;)
    {
        if (y & 1)
        {
            result = result * x % Mod;
        }
        x = x * x % Mod;
        y >>= 1;
    }
    return result;
}
void dfs(int u, int f)
{
    size[u] = 1;
    long long under = 0;
    for (const auto &v : g[u])
    {
        if (v == f)
        {
            continue;
        }
        dfs(v, u);
        under += 1ll * size[u] * size[v];
        size[u] += size[v];
    }
    int up;
    up = n - size[u];
    answer += fsp(2, under) - 1;
    answer += (fsp(2, 1ll * up * size[u]) - 1) * (fsp(2, under) - 1);
    answer %= Mod;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    printf("%lld\n", answer);
    return 0;
}