#include <cmath>
#include <cstdio>
int m, k;
long long n;
long long answer;
long long fsp(long long x, long long y)
{
    long long result = 1;
    for (; y != 0;)
    {
        if (y & 1)
        {
            result *= x;
        }
        x *= x;
        y >>= 1;
    }
    return result;
}
void solve()
{
    scanf("%lld%d", &n, &k);
    answer = 0;
    for (long long b = 1;; b++)
    {
        long long t = fsp(b, k) + n;
        if (t > 5e18)
        {
            break;
        }
        long long a = powl(t, 1.0 / k) + 1e-8;
        if (a == b)
        {
            break;
        }
        if (fsp(a, k) == t)
        {
            answer++;
        }
    }
    printf("%lld\n", answer);
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