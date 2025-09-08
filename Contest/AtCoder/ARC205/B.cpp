#include <cstdio>
constexpr int MaxN = 2e5 + 5;
int n, m;
int deg[MaxN];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        deg[u]++;
        deg[v]++;
    }
    int odd = 0;
    for (int i = 1; i <= n; i++)
    {
        odd += deg[i] % 2 == 1 ? 1 : 0;
        printf("%d\n", deg[i]);
    }
    printf("%d %d\n", odd, n - odd);
    printf("%lld\n", 1ll * n * (n - 1) / 2 - (n % 2 == 1 ? odd : n - odd) / 2);
    return 0;
}