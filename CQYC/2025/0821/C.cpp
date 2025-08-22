#include <algorithm>
#include <cstdio>
constexpr int MaxN = 8e3 + 5;
int n, m, k;
int p[MaxN];
int v[MaxN];
int best[MaxN];
long long dp[2][MaxN];
long long value[MaxN];
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= k; i++)
    {
        scanf("%d", &p[i]);
    }
    for (int i = 1; i <= k; i++)
    {
        scanf("%d", &v[i]);
    }
    for (int j = 1; j <= m; j++)
    {
        best[j] = -1;
    }
    for (int i = 1; i <= n; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        best[a] = std::max(best[a], b);
    }
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            if (best[j] != -1 && best[i - j] != -1)
            {
                best[i] = std::max(best[i], best[j] + best[i - j]);
            }
        }
        if (best[i] == -1)
        {
            value[i] = -0x3f3f3f3f;
            continue;
        }
        double c = 1.0 * best[i] / i;
        c -= 1e-7;
        c *= 100;
        for (int j = 1; j <= k; j++)
        {
            if (p[j - 1] < c && c <= p[j])
            {
                value[i] = i * v[j];
            }
        }
    }
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            dp[i & 1][j] = 0;
            if (j >= i)
            {
                dp[i & 1][j] = std::max(dp[i & 1][j], dp[~i & 1][j]);
                dp[i & 1][j] = std::max(dp[i & 1][j], dp[~i & 1][j - i] + value[i]);
                dp[i & 1][j] = std::max(dp[i & 1][j], dp[i & 1][j - i] + value[i]);
            }
            else
            {
                dp[i & 1][j] = std::max(dp[i & 1][j], dp[~i & 1][j]);
            }
        }
    }
    long long answer = 0;
    for (int i = 1; i <= n; i++)
    {
        answer = std::max(answer, dp[n & 1][m]);
    }
    printf("%lld\n", answer);
    return 0;
}