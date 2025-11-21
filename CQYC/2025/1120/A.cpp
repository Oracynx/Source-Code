#include <cstdio>
constexpr int MaxN = 1e1 + 5;
int n, m;
int d[MaxN];
long long fsp(long long x, long long y)
{
    long long r = 1;
    for (; y != 0;)
    {
        if (y & 1)
        {
            r = r * x;
        }
        y >>= 1;
        x = x * x;
    }
    return r;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &d[i]);
    }
    scanf("%d", &m);
    for (int t = 1; t <= m; t++)
    {
        long long x;
        scanf("%lld", &x);
        for (int len = 1;; len++)
        {
            long long all = d[1] == 0 ? (n - 1) * fsp(n, len - 1) : fsp(n, len);
            if (x > all)
            {
                x -= all;
                continue;
            }
            for (int i = 1; i <= len; i++)
            {
                long long once = fsp(n, len - i);
                long long ad = (x - 1) / once;
                printf("%d", i == 1 && d[1] == 0 ? d[ad + 1 + 1] : d[ad + 1]);
                x -= ad * once;
            }
            printf("\n");
            break;
        }
    }
    return 0;
}