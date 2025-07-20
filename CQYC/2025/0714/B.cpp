#include <cstdio>
#include <functional>
#include <queue>
#include <tuple>
#include <vector>
constexpr int MaxN = 5e6 + 5;
constexpr long long Mod = 1e9 + 7;
int n, m, k;
int p[MaxN];
int last[MaxN];
long long dp[MaxN];
std::priority_queue<std::tuple<int, int>, std::vector<std::tuple<int, int>>, std::greater<>> queue;
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
        last[p[i]] = i;
    }
    for (int i = 1; i <= k; i++)
    {
        queue.push({last[i], i});
    }
    for (int i = n + 1; i <= n + m; i++)
    {
        auto [_a, u] = queue.top();
        queue.pop();
        p[i] = u;
        last[u] = i;
        queue.push({i, u});
    }
    dp[0] = 1;
    for (int i = 1; i <= k; i++)
    {
        last[i] = 0;
    }
    for (int i = 1; i <= n + m; i++)
    {
        dp[i] = dp[i - 1] * 2;
        if (last[p[i]] != 0)
        {
            dp[i] -= dp[last[p[i]] - 1];
        }
        dp[i] %= Mod;
        dp[i] += Mod;
        dp[i] %= Mod;
        last[p[i]] = i;
    }
    printf("%lld\n", dp[n + m] - 1);
    return 0;
}