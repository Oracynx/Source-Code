#include <cstdio>
#include <map>
constexpr int MaxN = 1e6 + 5;
constexpr long long Mod = 998244353;
constexpr long long Base = 191;
constexpr long long HashMod = 975432499;
int n, m;
int p[MaxN];
long long w;
long long answer;
long long dp[MaxN];
long long val[MaxN];
int main()
{
    scanf("%d%d%lld", &n, &m, &w);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%lld", &val[i]);
    }
    for (int j = 1; j < 1 << n; j++)
    {
    }
    printf("%lld\n", answer);
    return 0;
}