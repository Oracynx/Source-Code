#include <cstdio>
constexpr int MaxN = 1e5 + 5;
int n;
int sum[MaxN];
char s[MaxN];
char t[MaxN];
bool func(int l, int r)
{
    return (sum[r] - sum[l - 1]) > (r - l + 1) / 2;
}
int main()
{
    scanf("%d", &n);
    scanf("%s", s + 1);
    scanf("%s", t + 1);
    for (int i = 1; i <= n; i++)
    {
        sum[i] = sum[i - 1] + (s[i] == '1' ? 1 : 0);
    }
    for (int k = 1; k <= n; k++)
    {
        bool suc = true;
        for (int i = k; i <= n; i++)
        {
            bool r = func(i - k + 1, i);
            if ((t[i] == '1' ? true : false) != r)
            {
                suc = false;
                break;
            }
        }
        printf("%d", suc ? 1 : 0);
    }
    return 0;
}