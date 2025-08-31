#include <algorithm>
#include <cstdio>
constexpr int MaxN = 2e1 + 5;
long long mem[MaxN][MaxN][MaxN];
long long fun(long long a, long long b, long long c)
{
    if (a <= 0 || b <= 0 || c <= 0)
    {
        return 1;
    }
    if (a > 20 || b > 20 || c > 20)
    {
        return fun(20, 20, 20);
    }
    if (mem[a][b][c] != 0)
    {
        return mem[a][b][c];
    }
    if (a < b && b < c)
    {
        return mem[a][b][c] = fun(a, b, c - 1) + fun(a, b - 1, c - 1) - fun(a, b - 1, c);
    }
    return mem[a][b][c] = fun(a - 1, b, c) + fun(a - 1, b - 1, c) + fun(a - 1, b, c - 1) - fun(a - 1, b - 1, c - 1);
}
int main()
{
    for (;;)
    {
        long long a, b, c;
        scanf("%lld%lld%lld", &a, &b, &c);
        if (a == -1 && b == -1 && c == -1)
        {
            break;
        }
        printf("w(%lld, %lld, %lld) = ", a, b, c);
        a = std::max(0ll, a);
        b = std::max(0ll, b);
        c = std::max(0ll, c);
        printf("%lld\n", fun(a, b, c));
    }
    return 0;
}