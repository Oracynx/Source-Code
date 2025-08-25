#include <cstdio>
long long n;
long long x;
int main()
{
    scanf("%lld", &n);
    x = 1;
    for (long long i = 1; i <= n; i++)
    {
        x *= i;
    }
    printf("%s\n", x % (n + 1) == 0 ? "YES" : "NO");
    return 0;
}