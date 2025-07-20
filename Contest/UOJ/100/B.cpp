#include <cstdio>
#include <iostream>
constexpr int MaxN = 5e2 + 5;
int n;
int a[MaxN];
int b[MaxN];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    // 贪心最优：排序后再做DP
    sort(a.begin() + 1, a.end());
    sort(b.begin() + 1, b.end());

    // dp[j][k]: 对当前 i，使用 b[1..j]，恰配 k 对的最小代价
    vector<vector<ll>> prev(n + 1, vector<ll>(n + 1, INF));
    vector<vector<ll>> cur(n + 1, vector<ll>(n + 1, INF));

    // 边界：k=0 时代价为 0
    for (int j = 0; j <= n; j++)
    {
        prev[j][0] = 0;
    }

    // 枚举 a 的前缀长度 i
    for (int i = 1; i <= n; i++)
    {
        // 重置 cur
        for (int j = 0; j <= n; j++)
        {
            fill(cur[j].begin(), cur[j].end(), INF);
            cur[j][0] = 0; // k=0 时始终 0
        }

        for (int j = 1; j <= n; j++)
        {
            ll cost = llabs(a[i] - b[j]);
            int lim = min(i, j);
            for (int k = 1; k <= lim; k++)
            {
                // 三种操作：不选 a[i]、不选 b[j]、匹配这对
                ll v1 = prev[j][k];                // 丢弃 a[i]
                ll v2 = cur[j - 1][k];             // 丢弃 b[j]
                ll v3 = prev[j - 1][k - 1] + cost; // 匹配 a[i] 和 b[j]
                cur[j][k] = min({v1, v2, v3});
            }
            // 同时保留 k=0 的边界
            cur[j][0] = 0;
        }
        // 滚动
        swap(prev, cur);
    }

    // 输出答案 ans[1..n]
    for (int k = 1; k <= n; k++)
    {
        cout << prev[n][k] << (k == n ? '\n' : ' ');
    }
    return 0;
}
