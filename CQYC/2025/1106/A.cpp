#include <cstdio>
long long n;
long long answer;
void solve()
{
    scanf("%lld", &n);
    answer = (n + 1) / 2;
    for (int j = 1; j <= 60; j += 2)
    {
        if ((1ll << (j + 1)) - 2 > n)
        {
            break;
        }
        answer++;
        long long cp = n - ((1ll << (j + 1)) - 2);
        for (int i = 60; i >= j + 2; i--)
        {
            if (1ll << i <= cp)
            {
                answer += 1ll << (i - j - 2);
                cp -= 1ll << i;
            }
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