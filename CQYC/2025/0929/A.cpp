#include <cstdio>
constexpr long long Mod = 998244353;
long long n;
long long answer;
int main()
{
    scanf("%lld", &n);
    answer = 1;
    n--;
    for (int j = 0; j < 63; j++)
    {
        long long x = 1ll << j;
        if (n > x)
        {
            n -= x;
            answer += (x % Mod) * (j + 2);
            answer %= Mod;
        }
        else
        {
            answer += (n % Mod) * (j + 2);
            answer %= Mod;
            break;
        }
    }
    printf("%lld\n", answer);
    return 0;
}