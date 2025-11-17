#include <cstdio>
constexpr int MaxN = 1e5 + 5;
int n, m;
int p[MaxN];
long long pre[MaxN];
long long qr(int l, int r)
{
    return pre[r] - pre[l - 1];
}
int main()
{
    scanf("%*d%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
        pre[i] = pre[i - 1] + p[i];
    }
    for (int i = 1; i <= m; i++)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        int d = r - l + 1;
        printf("%lld\n", d % 2 == 0 ? 2 * qr(r - d / 2 + 1, r) - 2 * qr(l, l + d / 2 - 1)
                                    : 2 * qr(r - d / 2 + 1, r) - (p[l] + p[l + d / 2]) - 2 * qr(l + 1, l + d / 2 - 1) +
                                          (p[l + d / 2] - p[l]));
    }
    return 0;
}
