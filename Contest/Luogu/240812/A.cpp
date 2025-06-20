#include <cstdio>
constexpr int MaxN = 5e3 + 5;
constexpr int Mod = 20080619;
int n;
int dp[2][MaxN][MaxN];
char s[MaxN];
int main()
{
    scanf("%d", &n);
    scanf("%s", s + 1);
    dp[0][0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            dp[0][i][j] = dp[0][i - 1][j];
            dp[1][i][j] = dp[1][i - 1][j];
            if (s[i] == 'u')
            {
                dp[0][i][j] += dp[0][i - 1][j] + (j >= 1 ? dp[1][i - 1][j - 1] : 0);
            }
            else if (s[i] == 'o')
            {
                dp[1][i][j] += dp[0][i - 1][j] + dp[1][i - 1][j];
            }
            else
            {
                dp[0][i][j] += dp[0][i - 1][j] + dp[1][i - 1][j];
            }
            dp[0][i][j] %= Mod;
            dp[1][i][j] %= Mod;
        }
    }
    for (int i = 0; i <= n; i++)
    {
        printf("%d ", (dp[0][n][i] + dp[1][n][i]) % Mod);
    }
    printf("\n");
    return 0;
}