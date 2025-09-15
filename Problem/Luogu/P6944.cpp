#include <algorithm>
#include <cstdio>
constexpr int MaxN = 5e2 + 5;
int n, d, r;
double c[MaxN][MaxN];
double f[MaxN][MaxN];
double g[MaxN][MaxN];
int main()
{
    scanf("%d%d%d", &n, &d, &r);
    c[0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        c[i][0] = 1;
        for (int j = 1; j <= i; j++)
        {
            c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
        }
    }
    f[0][n] = 1;
    for (int i = 0; i < d; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            for (int k = 1; k <= j; k++)
            {
                f[i + k][k] += f[i][j] * c[j][k];
                g[i + k][k] += (g[i][j] + std::min(k, r) * f[i][j]) * c[j][k];
            }
        }
    }
    double cf, cg;
    cf = 0;
    cg = 0;
    for (int i = 1; i <= n; i++)
    {
        cf += f[d][i];
        cg += g[d][i];
    }
    printf("%.8lf\n", cg / cf + r);
    return 0;
}