#include <cstdio>
constexpr int MaxN = 5e5 + 5;
int n, m;
int p[MaxN];
int w[MaxN];
int main()
{
    freopen("based.in", "r", stdin);
    freopen("based.out", "w", stdout);
    scanf("%d%d", &n, &m);
    bool spA = true;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
        w[i] = p[i];
        spA &= p[i] >= 1;
    }
    if (spA)
    {
        for (int i = 1; i <= m; i++)
        {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%d\n", l == 1 && r == n ? 0 : -1);
        }
        return 0;
    }
    long long pre = 0;
    long long answer = 0;
    for (int i = 1; i <= n; i++)
    {
        if (w[i] <= 0)
        {
            long long d = pre + w[i];
            if (d <= 0)
            {
                long long c = 1 - d;
                answer += c;
                w[i] += c;
            }
        }
        pre += w[i];
    }
    pre = 0;
    for (int i = n; i >= 1; i--)
    {
        if (w[i] <= 0)
        {
            long long d = pre + w[i];
            if (d <= 0)
            {
                long long c = 1 - d;
                answer += c;
                w[i] += c;
            }
        }
        pre += w[i];
    }
    for (int i = 1; i <= m; i++)
    {
        printf("%lld\n", answer);
    }
    return 0;
}