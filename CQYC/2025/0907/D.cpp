#include <cstdio>
constexpr int MaxN = 1e5 + 5;
constexpr long long Mod = 1e9 + 7;
int n, m, k;
int u[MaxN];
int v[MaxN];
long long answer;
long long fsp(long long x, long long y)
{
    return y == 1 ? x : y == 2 ? x * x % Mod : x * x % Mod * x % Mod;
}
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &u[i], &v[i]);
    }
    for (int j = 0; j < 1 << n; j++)
    {
        long long d = 0;
        for (int i = 1; i <= m; i++)
        {
            d += ((j >> (u[i] - 1)) & 1) && ((j >> (v[i] - 1)) & 1) ? 1 : 0;
        }
        answer += fsp(d, k);
        answer %= Mod;
    }
    printf("%lld\n", answer);
    return 0;
}