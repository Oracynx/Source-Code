#include <cstdio>
constexpr int MaxN = 3e5 + 5;
int n, m;
int p[MaxN];
long long s[MaxN];
long long f(int l, int r)
{
    return s[r] - s[l - 1];
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
        s[i] = s[i - 1] + p[i];
    }
    int px = 0;
    for (int i = 1; i <= m; i++)
    {
        int op;
        scanf("%d", &op);
        if (op == 1)
        {
            int c;
            scanf("%d", &c);
            px += c;
            if (px > n)
            {
                px -= n;
            }
        }
        else if (op == 2)
        {
            int l, r;
            scanf("%d%d", &l, &r);
            l += px;
            r += px;
            if (l > n)
            {
                l -= n;
            }
            if (r > n)
            {
                r -= n;
            }
            if (l <= r)
            {
                printf("%lld\n", f(l, r));
            }
            else
            {
                printf("%lld\n", f(1, r) + f(l, n));
            }
        }
    }
    return 0;
}