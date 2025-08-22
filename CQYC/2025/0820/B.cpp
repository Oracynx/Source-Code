#include <algorithm>
#include <cstdio>
constexpr int MaxN = 2e5 + 5;
constexpr int MaxK = 6e2 + 5;
int id;
int n, m, k;
int p[MaxN];
int c[MaxN];
bool have[MaxK];
bool temp[MaxK];
void solve()
{
    scanf("%d%d%d", &n, &k, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
        p[i] %= k;
    }
    if (k == 1)
    {
        for (int i = 1; i <= m; i++)
        {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%d\n", 0);
        }
        return;
    }
    if (9 <= id && id <= 12)
    {
        int g = 1;
        c[0] = g;
        for (int i = 1; i <= n; i++)
        {
            c[i] = std::max(c[i - 1], (g = g * p[1] % k));
        }
        for (int i = 1; i <= m; i++)
        {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%d\n", c[r - l + 1]);
        }
        return;
    }
    for (int i = 1; i <= m; i++)
    {
        for (int j = 0; j < k; j++)
        {
            have[j] = false;
        }
        have[1] = true;
        int l, r;
        scanf("%d%d", &l, &r);
        for (int j = l; j <= r; j++)
        {
            for (int c = 0; c < k; c++)
            {
                temp[(c * p[j]) % k] |= have[c];
            }
            temp[p[j]] = true;
            for (int c = 0; c < k; c++)
            {
                have[c] |= temp[c];
                temp[c] = false;
            }
        }
        int answer = 1;
        for (int j = k - 1; j >= 0; j--)
        {
            if (have[j])
            {
                answer = j;
                break;
            }
        }
        printf("%d\n", answer);
    }
}
int main()
{
    freopen("love.in", "r", stdin);
    freopen("love.out", "w", stdout);
    int id, t;
    scanf("%d%d", &id, &t);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}