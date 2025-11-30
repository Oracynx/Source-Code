#include <algorithm>
#include <cstdio>
#include <numeric>
constexpr int MaxN = 1e1 + 5;
int p[MaxN];
int solve()
{
    for (int i = 1; i <= 9; i++)
    {
        scanf("%d", &p[i]);
    }
    long long sum = std::accumulate(p + 1, p + 1 + 9, 0ll);
    long long other = sum - p[5];
    if (p[5] > 0)
    {
        printf("%lld\n", std::max(0ll, (p[5] - 1) - other));
        return 0;
    }
    bool suc = false;
    for (int k = 1; k <= 4; k++)
    {
        if (p[k] > 0 && p[10 - k] > 0)
        {
            long long ps = p[k] + p[10 - k];
            if (sum - ps == 0)
            {
                suc = true;
                break;
            }
        }
    }
    if (suc)
    {
        printf("1\n");
    }
    else
    {
        printf("0\n");
    }
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