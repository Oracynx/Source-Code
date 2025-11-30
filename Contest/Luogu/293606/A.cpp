#include <algorithm>
#include <cstdio>
constexpr int MaxN = 1e4 + 5;
int n;
int a[MaxN];
int b[MaxN];
int c[MaxN];
double f(int w, double x)
{
    return a[w] * x * x + b[w] * x + c[w];
}
double g(double x)
{
    double r = -1e18;
    for (int i = 1; i <= n; i++)
    {
        r = std::max(r, f(i, x));
    }
    return r;
}
int solve()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d%d", &a[i], &b[i], &c[i]);
    }
    double l, r;
    l = 0;
    r = 1000;
    for (; r - l > 1e-11;)
    {
        double d = (r - l) / 3;
        double dl, dr;
        dl = g(l + d);
        dr = g(l + d + d);
        if (dl > dr)
        {
            l = l + d;
        }
        else
        {
            r = r - d;
        }
    }
    printf("%.4lf\n", g(l));
    return 0;
}
int main()
{
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}