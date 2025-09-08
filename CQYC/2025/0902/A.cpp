#include <cstdio>
#include <vector>
constexpr int MaxN = 5e3 + 5;
constexpr long long Mod = 998'244'353;
int n, m;
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
        y >>= 1;
        x = x * x % Mod;
    }
    return result;
}
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
    printf("%lld\n", fsp(2, n * (n - 1) / 2 - m));
    return 0;
}