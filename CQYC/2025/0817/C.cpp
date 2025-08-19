#include <cstdio>
constexpr int MaxN = 1e5 + 5;
constexpr long long Mod = 1e9 + 7;
int m;
long long n, c;
long long once;
long long answer[MaxN];
long long fsp(long long x, long long y)
{
    long long result = 1;
    for (; y != 0;)
    {
        if (y & 1)
        {
            result = result * x % Mod;
        }
        x = x * x % Mod;
        y >>= 1;
    }
    return result;
}
long long inv(long long x)
{
    return fsp(x, Mod - 2);
}
int main()
{
    scanf("%lld%d", &n, &m);
    c = (fsp(2, n) - 1 + Mod) % Mod;
    once = (1 + c) * c % Mod * inv(2) % Mod;
    if (n <= 1e5)
    {
        answer[n] = c;
        long long cp = c;
        long long size = 1;
        for (int i = n - 1; i >= 1; i--)
        {
            cp--;
            cp = cp * inv(2) % Mod;
            answer[i] = answer[i + 1] * 2 - size + cp + Mod;
            answer[i] %= Mod;
            size = size * 4 + 1;
            size %= Mod;
        }
    }
    for (int i = 1; i <= m; i++)
    {
        long long x;
        scanf("%lld", &x);
        scanf("%*s");
        if (x == 1)
        {
            printf("%lld\n", once);
        }
        else
        {
            printf("%lld\n", answer[x]);
        }
    }
    return 0;
}