#include <algorithm>
#include <cstdio>
constexpr int MaxN = 3e3 + 5;
int n, m;
long long p[MaxN][MaxN];
long long dp[3][MaxN][MaxN];
void solve()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            scanf("%lld", &p[i][j]);
        }
    }
    for (int i = 0; i <= n + 1; i++)
    {
        for (int j = 0; j <= m + 1; j++)
        {
            dp[0][i][j] = dp[1][i][j] = dp[2][i][j] = 0;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            dp[0][i][j] = std::max(dp[0][i - 1][j], dp[1][i - 1][j]) + p[i][j];
            dp[1][i][j] = std::max(dp[0][i][j - 1], dp[1][i][j - 1]) + p[i][j];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            dp[2][i + 1][j - 1] =
                std::max(dp[2][i + 1][j - 1], std::max(dp[0][i][j] + p[i][j - 1], dp[1][i][j]) + p[i + 1][j - 1]);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            dp[2][i][j] = std::max(dp[2][i][j], std::max(dp[2][i - 1][j], dp[2][i][j - 1]) + p[i][j]);
        }
    }
    printf("%lld\n", std::max({dp[0][n][m], dp[1][n][m], dp[2][n][m]}));
}
int main()
{
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; ++i)
    {
        solve();
    }
    return 0;
}