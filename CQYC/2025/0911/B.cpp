#include <algorithm>
#include <cstdio>
constexpr int MaxN = 3e5 + 5;
int n;
long long m;
long long a[MaxN];
long long b[MaxN];
bool check(long long x)
{
    long long cost = 0;
    for (int i = 1; i <= n; i++)
    {
        long long origin = a[i] * m;
        if (origin >= x)
        {
            cost += x / a[i] + (x % a[i] != 0 ? 1 : 0);
        }
        else
        {
            long long need = (x - origin);
            cost += m + need / b[i] + (need % b[i] != 0 ? 1 : 0);
        }
        if (cost > n * m)
        {
            return false;
        }
    }
    return cost <= n * m;
}
int main()
{
    scanf("%d%lld", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &b[i]);
        a[i] = std::max(a[i], b[i]);
    }
    long long l, r;
    l = 0;
    r = 1e18;
    long long answer = -1;
    for (; l <= r;)
    {
        long long mid = (l + r) / 2;
        if (check(mid))
        {
            answer = mid;
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    printf("%lld\n", answer);
    return 0;
}