#include <algorithm>
#include <cstdio>
constexpr int MaxN = 1e5 + 5;
constexpr int MaxM = 7;
int n;
int p[MaxN];
int l[MaxM][MaxM];
int r[MaxM][MaxM];
long long answer;
long long dp[MaxM][MaxM][MaxN];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }
    for (int i = 1; i <= 5; i++)
    {
        for (int j = 1; j <= 5; j++)
        {
            scanf("%d", &l[i][j]);
        }
    }
    for (int i = 1; i <= 5; i++)
    {
        for (int j = 1; j <= 5; j++)
        {
            scanf("%d", &r[i][j]);
        }
    }
    for (int k = 1; k <= 5; k++)
    {
        for (int i = 1; i <= 5; i++)
        {
            for (int j = 1; j <= 5; j++)
            {
                l[i][j] = std::min(l[i][j], l[i][k] + l[k][j]);
            }
        }
    }
    for (int k = 1; k <= 5; k++)
    {
        for (int i = 1; i <= 5; i++)
        {
            for (int j = 1; j <= 5; j++)
            {
                r[i][j] = std::min(r[i][j], r[i][k] + r[k][j]);
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int a = 1; a <= 5; a++)
        {
            for (int b = 1; b <= 5; b++)
            {
                dp[a][b][i] = 0x3f3f3f3f'3f3f3f3f;
            }
        }
        for (int a = 1; a <= 5; a++)
        {
            for (int b = 1; b <= 5; b++)
            {
                dp[p[i]][b][i] = std::min(dp[p[i]][b][i], dp[a][b][i - 1] + l[a][p[i]]);
                dp[a][p[i]][i] = std::min(dp[a][p[i]][i], dp[a][b][i - 1] + r[b][p[i]]);
            }
        }
    }
    answer = 0x3f3f3f3f'3f3f3f3f;
    for (int i = 1; i <= 5; i++)
    {
        for (int j = 1; j <= 5; j++)
        {
            answer = std::min(answer, dp[i][j][n]);
        }
    }
    printf("%lld\n", answer);
    return 0;
}