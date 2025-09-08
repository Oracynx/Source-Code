#include <cstdio>
constexpr int MaxN = 1e6 + 5;
constexpr long long Mod = 1e9 + 7;
int n;
int p[MaxN];
long long answer;
long long f[MaxN];
long long g[MaxN];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }
    f[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        if (p[i] >= 1)
        {
            g[p[i]] += g[p[i]] + f[p[i] - 1];
            g[p[i]] %= Mod;
        }
        g[p[i] + 2] += g[p[i] + 2];
        g[p[i] + 2] %= Mod;
        f[p[i] + 1] += f[p[i]] + f[p[i] + 1];
        f[p[i] + 1] %= Mod;
    }
    for (int i = 0; i <= 1e6; i++)
    {
        answer += f[i] + g[i];
        answer %= Mod;
    }
    printf("%lld\n", (answer - 1 + Mod) % Mod);
    return 0;
}