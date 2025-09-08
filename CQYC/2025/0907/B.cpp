#include <algorithm>
#include <cstdio>
#include <vector>
typedef __int128 int128;
constexpr int MaxN = 1e5 + 5;
int n, m;
int128 p[2][MaxN];
std::vector<int128> v;
int main()
{
    scanf("%*d");
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        long long x;
        scanf("%lld", &x);
        p[0][i] = x;
    }
    for (int i = 1; i <= n; i++)
    {
        long long x;
        scanf("%lld", &x);
        p[1][i] = x;
    }
    for (int i = 1; i <= m; i++)
    {
        v.clear();
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        long long ca, cb, cc, cd, ce;
        for (int u = 0; u < 2; u++)
        {
            scanf("%lld%lld%lld%lld%lld", &ca, &cb, &cc, &cd, &ce);
            int128 a, b, c, d, e;
            a = ca;
            b = cb;
            c = cc;
            d = cd;
            e = ce;
            for (int j = l; j <= r; j++)
            {
                v.push_back(a + b * p[u][j] + c * p[u][j] * p[u][j] + d * p[u][j] * p[u][j] * p[u][j] +
                            e * p[u][j] * p[u][j] * p[u][j] * p[u][j]);
            }
        }
        std::sort(v.begin(), v.end());
        auto answer = v[k - 1];
        std::vector<char> ad;
        for (; answer != 0;)
        {
            ad.push_back(answer % 10 + '0');
            answer /= 10;
        }
        std::reverse(ad.begin(), ad.end());
        for (const auto &val : ad)
        {
            printf("%c", val);
        }
        printf("\n");
    }
    return 0;
}