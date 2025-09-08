#include <cstdio>
constexpr int MaxN = 1e5 + 5;
constexpr long long Mod = 1e9 + 7;
int n, m;
int l[MaxN];
int r[MaxN];
int op[MaxN];
long long cf[MaxN];
long long acf[MaxN];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &op[i], &l[i], &r[i]);
    }
    acf[m]++;
    long long ad = 0;
    for (int i = m; i >= 1; i--)
    {
        ad += acf[i];
        ad %= Mod;
        if (op[i] == 1)
        {
            cf[l[i]] += ad;
            cf[l[i]] %= Mod;
            cf[r[i] + 1] -= ad;
            cf[r[i] + 1] %= Mod;
            cf[r[i] + 1] += Mod;
            cf[r[i] + 1] %= Mod;
        }
        else if (op[i] == 2)
        {
            acf[r[i]] += ad;
            acf[r[i]] %= Mod;
            acf[l[i] - 1] -= ad;
            acf[l[i] - 1] %= Mod;
            acf[l[i] - 1] += Mod;
            acf[l[i] - 1] %= Mod;
        }
    }
    long long answer = 0;
    for (int i = 1; i <= n; i++)
    {
        answer += cf[i];
        answer %= Mod;
        printf("%lld ", answer);
    }
    printf("\n");
    return 0;
}