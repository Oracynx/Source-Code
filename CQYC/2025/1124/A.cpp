#include <cstdio>
#include <cstdlib>
#include <cstring>
constexpr int MaxN = 1e6 + 5;
constexpr long long Mod = 998'244'353;
int n;
int p[MaxN];
long long answer;
long long g[MaxN];
long long f[2][5][5];
int solve()
{
    memset(f, 0, sizeof(f));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }
    if (n == 1)
    {
        printf("1\n");
        return 0;
    }
    if (n == 2)
    {
        printf("%d\n", abs(p[1] - p[2]) == 1 ? 2 : 1);
        return 0;
    }
    f[2 & 1][0][1] = 1;
    if (abs(p[1] - p[2]) == 1)
    {
        f[2 & 1][1][0] = 1;
    }
    for (int i = 3; i <= n; i++)
    {
        memset(f[i & 1], 0, sizeof(long long) * 5 * 5);
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < 5; k++)
            {
                f[i & 1][0][j + 1] += f[~i & 1][j][k];
                f[i & 1][0][j + 1] %= Mod;
                if (abs(p[i] - p[i - 1 - j]) == 1)
                {
                    f[i & 1][j + 1][0] += f[~i & 1][j][k];
                    f[i & 1][j + 1][0] %= Mod;
                    if (abs(p[i] - p[i - 1 - k]) == 1)
                    {
                        f[i & 1][j + 1][k + 1] += f[~i & 1][j][k];
                        f[i & 1][j + 1][k + 1] %= Mod;
                    }
                }
            }
        }
    }
    answer = 0;
    for (int j = 0; j < 5; j++)
    {
        for (int k = 0; k < 5; k++)
        {
            answer += f[n & 1][j][k];
        }
    }
    answer %= Mod;
    printf("%lld\n", answer);
    return 0;
}
int main()
{
    int c, t;
    scanf("%d%d", &c, &t);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}