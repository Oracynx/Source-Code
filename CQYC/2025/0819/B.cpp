#include <algorithm>
#include <cstdio>
#include <numeric>
constexpr int MaxN = 5e3 + 5;
int n;
int cnt;
int a[MaxN];
int f[MaxN];
int fa[MaxN];
int answer[MaxN];
int main()
{
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
    {
        scanf("%d", &fa[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    std::iota(f + 1, f + 1 + n, 1);
    for (;;)
    {
        bool suc = true;
        for (int i = 2; i <= n; i++)
        {
            if (f[fa[i]] > f[i])
            {
                suc = false;
                break;
            }
        }
        if (suc)
        {
            cnt++;
            for (int i = 1; i <= n; i++)
            {
                answer[i] = f[i];
            }
        }
        bool eq = true;
        for (int i = 1; i <= n; i++)
        {
            eq &= f[i] == a[i];
        }
        if (eq)
        {
            break;
        }
        if (!std::next_permutation(f + 1, f + 1 + n))
        {
            break;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", answer[i]);
    }
    printf("\n");
    printf("%d\n", cnt);
    return 0;
}