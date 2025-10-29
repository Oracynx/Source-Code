#include <algorithm>
#include <cmath>
#include <cstdio>
long long n, m;
long long len(long long n)
{
    return n == 0 ? 1 : n < 10 ? 1 : len(n / 10) + 1;
}
long long solve()
{
    scanf("%lld%lld", &n, &m);
    long long y_min = n + 1;
    long long y_max = n + m;
    long long k_1 = len(y_min);
    long long k_2 = len(y_max);
    long long ans = 0;
    long long p10_k = 1;
    for (int i = 0; i < k_1; ++i)
    {
        p10_k *= 10;
    }
    long long p10_k_1 = (k_1 == 1) ? 1 : (p10_k / 10);
    for (long long k = k_1; k <= k_2; ++k)
    {
        long long y_start_k = std::max(y_min, p10_k_1);
        long long y_end_k = std::min(y_max, p10_k - 1);

        // 如果这个 k 值下没有有效的 y，跳过
        if (y_start_k > y_end_k)
        {
            // 为下一次迭代准备 10 的幂
            if (k < k_2)
            {
                p10_k *= 10;
                p10_k_1 *= 10;
                if (p10_k_1 == 0)
                {
                    p10_k_1 = 1; 
                }
            }
            continue;
        }
        long long L = n * p10_k + y_start_k;
        long long R = n * p10_k + y_end_k;
        long long m_max = (long long)sqrtl(R);
        long long m_min = (long long)sqrtl(L);
        if (m_min * m_min < L)
        {
            m_min++;
        }
        if (m_min <= m_max)
        {
            ans += (m_max - m_min + 1);
        }
        if (k < k_2)
        {
            p10_k *= 10;
            p10_k_1 *= 10;
            if (p10_k_1 == 0)
                p10_k_1 = 1;
        }
    }
    printf("%lld\n", ans);
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