#include <cstdio>
#include <map>
constexpr int MaxN = 1e6 + 5;
constexpr long long Mod = 998244353;
constexpr long long Base = 191;
constexpr long long HashMod = 975432499;
int n, m;
int p[MaxN];
long long w;
long long answer;
long long val[MaxN];
std::map<long long, bool> map;
int main()
{
    freopen("poem.in", "r", stdin);
    freopen("poem.out", "w", stdout);
    scanf("%d%d%lld", &n, &m, &w);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%lld", &val[i]);
    }
    if (n <= 20)
    {
        for (int j = 1; j < 1 << n; j++)
        {
            long long hash = 0;
            long long temp = 0;
            for (int i = 1; i <= n; i++)
            {
                if ((j >> (i - 1)) & 1)
                {
                    temp = temp * w + val[p[i]];
                    temp %= Mod;
                    hash = hash * Base + p[i];
                    hash %= HashMod;
                }
            }
            if (map[hash])
            {
                continue;
            }
            map[hash] = true;
            answer += temp;
            answer %= Mod;
        }
        printf("%lld\n", answer);
        return 0;
    }
    return 0;
}