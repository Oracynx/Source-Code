#include <cstdio>
constexpr int MaxN = 1e6 + 5;
int n;
int p[MaxN];
void solve()
{
    scanf("%d", &n);
    bool spA = true;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
        spA &= p[i] == 0;
    }
    if (spA)
    {
        if (n <= 3)
        {
            printf("%d\n", 1);
            return;
        }
        if (n <= 5)
        {
            printf("%d\n", 2);
            return;
        }
        if (n <= 6)
        {
            printf("%d\n", 3);
        }
        int c = (n + 1) / 2;
        int answer = 1;
        c -= 3;
        for (;;)
        {
            c++;
            if (c <= 3)
            {
                break;
            }
            c -= 3;
            answer++;
        }
        int still = n / 2;
        still -= (3 - c);
        answer++;
        answer += still;
        printf("%d\n", answer);
    }
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