#include <cstdio>
constexpr int MaxN = 5e5 + 5;
constexpr long long Mod = 998'244'353;
int n, q;
int a, b;
int s[MaxN];
long long t;
long long p[MaxN];
long long fsp(long long x, long long y)
{
    long long res = 1;
    for (; y != 0;)
    {
        if (y & 1)
        {
            res = res * x % Mod;
        }
        y >>= 1;
        x = x * x % Mod;
    }
    return res;
}
long long inv(long long x)
{
    return fsp(x, Mod - 2);
}
long long frac(long long x, long long y)
{
    return x * inv(y) % Mod;
}
long long calc(int l, int r)
{
    long long base = 0;
    for (int i = l; i <= r; i++)
    {
        base += s[i];
    }
    base *= a;
    base %= Mod;
    long long f = 0;
    long long combo = 0;
    for (int i = l; i <= r; i++)
    {
        if (i == l)
        {
            f = s[i];
        }
        else if (i != l ^ s[i] == 1)
        {
            f = f + 1;
        }
        else
        {
            f = f * t;
        }
        f %= Mod;
        combo += s[i] * f;
        combo %= Mod;
    }
    combo *= b;
    combo %= Mod;
    return (base + combo) % Mod;
}
long long dfs(int u, long long px, int l, int r)
{
    if (u > r)
    {
        return calc(l, r) * px % Mod;
    }
    long long res = 0;
    s[u] = 1;
    res += dfs(u + 1, px * p[u] % Mod, l, r);
    s[u] = 0;
    res += dfs(u + 1, px * (1 - p[u] + Mod) % Mod, l, r);
    return res;
}
int main()
{
    freopen("iiidx.in", "r", stdin);
    freopen("iiidx.out", "w", stdout);
    scanf("%*d");
    int ta, tb;
    scanf("%d%d%d%d%d%d", &n, &q, &ta, &tb, &a, &b);
    t = frac(ta, tb);
    for (int i = 1; i <= n; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        p[i] = frac(a, b);
    }
    for (int i = 1; i <= q; i++)
    {
        int op;
        scanf("%d", &op);
        if (op == 0)
        {
            int x, a, b;
            scanf("%d%d%d", &x, &a, &b);
            p[x] = frac(a, b);
        }
        else if (op == 1)
        {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%lld\n", dfs(l, 1, l, r));
        }
    }
    return 0;
}