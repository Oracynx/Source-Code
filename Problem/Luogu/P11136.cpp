#include <cstdio>
constexpr long long Mod = 988'444'333;
long long a, b, h, k;
int main()
{
    scanf("%lld%lld%lld%lld", &a, &b, &h, &k);
    printf("%lld\n", (a + k) * (b + k) * (h + k) % Mod);
    return 0;
}