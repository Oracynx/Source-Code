#include <cstdio>
#include <numeric>
constexpr int MaxN = 1e2 + 5;
int n, m;
int p[MaxN];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }
    int all = std::accumulate(p + 1, p + 1 + n, 0);
    for (int i = 1; i <= n; i++)
    {
        if (all - p[i] == m)
        {
            printf("Yes\n");
            return 0;
        }
    }
    printf("No\n");
    return 0;
}