#include <cstdio>
constexpr int MaxN = 2e5 + 5;
int n, m;
long long answer;
long long d[MaxN];
long long pd[MaxN];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int p;
        long long x;
        scanf("%d%lld", &p, &x);
        if (p >= 2)
        {
            d[p - 1] -= x;
            if (d[p - 1] > pd[p - 1])
            {
                pd[p - 1] = d[p - 1];
            }
        }
        if (p <= n - 1)
        {
            d[p] += x;
            if (d[p] > pd[p])
            {
                pd[p] = d[p];
            }
        }
    }
    answer = n;
    for (int i = 1; i <= n - 1; i++)
    {
        long long di = pd[i] + 1;
        answer += (n - i) * di;
    }
    printf("%lld\n", answer);
    return 0;
}