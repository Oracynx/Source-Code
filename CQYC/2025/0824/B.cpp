#include <algorithm>
#include <csetjmp>
#include <cstdio>
constexpr int MaxN = 1e2 + 5;
constexpr long long Mod = 998'244'353;
int n;
int a, b, c;
long long dp[2][MaxN][MaxN][MaxN];
int main()
{
    scanf("%d%d%d%d", &n, &a, &b, &c);
    dp[0 & 1][0][0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int x = 0; x <= std::min(i, a); x++)
        {
            for (int y = 0; y <= std::min(i, b); y++)
            {
                for (int z = 0; z <= std::min(i, c); z++)
                {
                    dp[i & 1][x][y][z] = 0;
                    if (x >= 1)
                    {
                        dp[i & 1][x][y][z] += dp[(i - 1) & 1][x - 1][y][z];
                    }
                    if (y >= 1)
                    {
                        dp[i & 1][x][y][z] += dp[(i - 1) & 1][x][y - 1][z];
                    }
                    if (z >= 1)
                    {
                        dp[i & 1][x][y][z] += dp[(i - 1) & 1][x][y][z - 1];
                    }
                    if (x >= 1 && y >= 1)
                    {
                        dp[i & 1][x][y][z] += dp[(i - 1) & 1][x - 1][y - 1][z];
                    }
                    if (x >= 1 && z >= 1)
                    {
                        dp[i & 1][x][y][z] += dp[(i - 1) & 1][x - 1][y][z - 1];
                    }
                    if (y >= 1 && z >= 1)
                    {
                        dp[i & 1][x][y][z] += dp[(i - 1) & 1][x][y - 1][z - 1];
                    }
                    if (x >= 1 && y >= 1 && z >= 1)
                    {
                        dp[i & 1][x][y][z] += dp[(i - 1) & 1][x - 1][y - 1][z - 1];
                    }
                    dp[i & 1][x][y][z] %= Mod;
                }
            }
        }
    }
    long long answer = 0;
    for (int x = 0; x <= a; x++)
    {
        for (int y = 0; y <= b; y++)
        {
            for (int z = 0; z <= c; z++)
            {
                answer += dp[n & 1][x][y][z];
                answer %= Mod;
            }
        }
    }
    printf("%lld\n", answer);
    return 0;
}