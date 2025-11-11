#include <algorithm>
#include <cstdio>
constexpr int MaxN = 1e7 + 5;
int n;
char s[MaxN];
void solve()
{
    scanf("%d", &n);
    scanf(" ");
    bool sa, sb;
    sa = sb = true;
    for (int i = 1; i <= n; i++)
    {
        s[i] = getchar();
        sa &= s[i] == '0';
        sb &= s[i] == '1';
    }
    if (sa)
    {
        putchar('0');
        putchar('\n');
        return;
    }
    if (sb)
    {
        for (int i = 1; i <= n - 1; i++)
        {
            putchar('1');
        }
        putchar('0');
        putchar('\n');
        return;
    }
    int ad;
    ad = 1;
    for (int i = 1; i <= n; i++)
    {
        if (s[i] == '1')
        {
            break;
        }
        ad++;
    }
    int one = 0;
    for (int i = ad; i <= n; i++)
    {
        if (s[i] == '0')
        {
            break;
        }
        one++;
    }
    int zero = 0;
    for (int i = ad + one; i <= n; i++)
    {
        if (s[i] == '1')
        {
            break;
        }
        zero++;
    }
    int choose = std::min(one, zero);
    int cur = ad + (one - choose);
    for (int i = ad; i <= ad + one - 1; i++)
    {
        putchar(s[i]);
    }
    for (int i = ad + one; i <= n; i++)
    {
        putchar(s[i] != s[cur++] ? '1' : '0');
    }
    putchar('\n');
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