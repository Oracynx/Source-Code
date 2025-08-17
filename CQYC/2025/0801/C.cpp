#include <cstdio>
int n, k;
long long Mod;
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
int main()
{
    scanf("%d%lld%d", &n, &Mod, &k);
    printf("%lld\n", fsp(fsp(2, n), n));
    return 0;
}