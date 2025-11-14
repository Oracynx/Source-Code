#include <cstdio>
constexpr int MaxN = 3e6 + 5;
constexpr long long Mod = 998'244'353;
int n, m, q, k;
long long answer;
long long fact[MaxN];
long long ifact[MaxN];
long long fsp(long long x, long long y)
{
    long long r = 1;
    for (; y != 0;)
    {
        if (y & 1)
        {
            r = r * x % Mod;
        }
        x = x * x % Mod;
        y >>= 1;
    }
    return r;
}
long long inv(long long x)
{
    return fsp(x, Mod - 2);
}
int main()
{
    scanf("%d%d%d%d", &n, &m, &q, &k);
    if (m > q)
    {
        printf("0\n");
        return 0;
    }
    answer = n - m + 1;
    fact[0] = 1;
    ifact[0] = 1;
    for (int i = 1; i <= m; i++)
    {
        fact[i] = fact[i - 1] * i % Mod;
    }
    ifact[m] = inv(fact[m]);
    for (int i = m - 1; i >= 1; i--)
    {
        ifact[i] = ifact[i + 1] * (i + 1) % Mod;
    }
    long long temp = 0;
    for (int i = 0; i <= m; i++)
    {
        temp += fact[m] * ifact[m - i] % Mod * ifact[i] % Mod * fsp(n - i, q) % Mod * (i % 2 == 0 ? 1 : -1);
    }
    temp %= Mod;
    temp += Mod;
    answer = answer * temp % Mod * fsp(k, q - m) % Mod;
    printf("%lld\n", answer);
    return 0;
}