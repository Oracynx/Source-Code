#include <algorithm>
#include <cmath>
#include <cstdio>
#include <map>
#include <tuple>
#include <utility>
constexpr long long SOLVE_SIZE = 1.3e6;
long long n;
std::map<long long, std::tuple<long long, long long>> map;
long long gcd(long long x, long long y)
{
    for (;;)
    {
        if (x < y)
        {
            std::swap(x, y);
        }
        if (y == 0)
        {
            return x;
        }
        x %= y;
    }
}
bool check(long long n, long long i)
{
    if (i == n)
    {
        printf("%lld %lld\n", i, i);
        return true;
    }
    if (i * (i + 1) > n)
    {
        printf("%lld %lld\n", n, n);
        return true;
    }
    long long x = i;
    for (long long j = i + 1;; j++)
    {
        __int128 cp = x;
        cp *= j;
        cp /= gcd(x, j);
        if (cp > n)
        {
            break;
        }
        x = cp;
        if (x == n)
        {
            printf("%lld %lld\n", i, j);
            return true;
        }
    }
    return false;
}
bool want(long long n, long long x)
{
    for (long long i = std::max(1ll, x - 3); i <= x + 3; i++)
    {
        if (check(n, i))
        {
            return true;
        }
    }
    return false;
}
bool solve(long long n, long long begin = 1, long long limit = 1e9)
{
    for (long long i = begin; i <= limit; i++)
    {
        if (check(n, i))
        {
            return true;
        }
    }
    return false;
}
void solve()
{
    scanf("%lld", &n);
    if (solve(n, 1, SOLVE_SIZE))
    {
        return;
    }
    for (int i = 3; i >= 2; i--)
    {
        if (want(n, (long long)(powl(n, 1.0 / i))))
        {
            return;
        }
        if (want(n, (long long)(powl(n * 2, 1.0 / i))))
        {
            return;
        }
    }
    printf("%lld %lld\n", n, n);
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