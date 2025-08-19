#include <algorithm>
#include <cstdio>
constexpr int MaxN = 2e5 + 5;
int n, m;
long long p[MaxN];
long long w[MaxN];
long long left[MaxN];
long long right[MaxN];
long long answer[MaxN];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &p[i]);
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%lld", &w[i]);
    }
    long long c = 0;
    for (int i = 1; i <= m; i++)
    {
        c += w[i];
        left[i] = std::max(left[i - 1], c <= 0 ? -c : 0);
        right[i] = std::max(right[i - 1], c >= 0 ? c : 0);
    }
    answer[1] += left[m];
    answer[n] += right[m];
    for (int i = 1; i <= n - 1; i++)
    {
        long long d = p[i + 1] - p[i];
        int l, r;
        l = 0;
        r = m;
        int e = -1;
        for (; l <= r;)
        {
            int mid = (l + r) / 2;
            if (left[mid] + right[mid] <= d)
            {
                e = mid;
                l = mid + 1;
            }
            else
            {
                r = mid - 1;
            }
        }
        answer[i] += right[e];
        answer[i + 1] += left[e];
        if (e <= m - 1)
        {
            answer[w[e + 1] > 0 ? i : i + 1] += d - left[e] - right[e];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        printf("%lld\n", answer[i]);
    }
    return 0;
}