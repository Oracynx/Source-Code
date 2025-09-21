#include <algorithm>
#include <cstdio>
#include <cstring>
constexpr int MaxN = 1e5 + 5;
int n;
long long p[MaxN];
long long dp[MaxN];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &p[i]);
    }
    std::fill(dp, dp + MaxN, -0x3f3f3f3f'3f3f3f3f);
    dp[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j >= 1; j--)
        {
            dp[j] = std::max(dp[j], dp[j - 1] + j * p[i]);
        }
    }
    long long answer = 0;
    for (int i = 1; i <= n; i++)
    {
        answer = std::max(answer, dp[i]);
    }
    printf("%lld\n", answer);
    return 0;
}