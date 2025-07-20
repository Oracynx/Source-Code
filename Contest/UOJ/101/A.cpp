#include <algorithm>
#include <cstdio>
constexpr int MaxN = 8e3 + 5;
constexpr long long Mod = 998244353;
int id;
int n, k;
int p[MaxN];
int f[MaxN];
int s[MaxN];
int pos[MaxN];
bool vis[MaxN];
long long c[MaxN];
long long dp[2][MaxN];
bool check()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
            {
                continue;
            }
            if (s[i] > j + k && s[j] > i + k)
            {
                return false;
            }
        }
    }
    return true;
}
void solve()
{
    scanf("%d%d", &n, &k);
    int sp1 = true;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
        sp1 &= p[i] == 0;
    }
    if (k == 0 && sp1)
    {
        printf("%lld\n", c[n]);
        return;
    }
    if (n <= 10)
    {
        for (int i = 1; i <= n; i++)
        {
            vis[i] = false;
        }
        for (int i = 1; i <= n; i++)
        {
            vis[p[i]] = true;
        }
        int m = 0;
        for (int i = 1; i <= n; i++)
        {
            if (!vis[i])
            {
                f[++m] = i;
            }
        }
        int answer = 0;
        for (;;)
        {
            int cur = 1;
            for (int i = 1; i <= n; i++)
            {
                s[i] = p[i] == 0 ? f[cur++] : p[i];
            }
            bool ok = true;
            if (k == 0)
            {
                for (int i = 1; i < n; ++i)
                {
                    if (s[i] > i + 1)
                    {
                        ok = false;
                        break;
                    }
                }
            }
            else
            {
                ok = check();
            }
            if (ok)
            {
                answer++;
            }
            if (m == 0 || !std::next_permutation(f + 1, f + 1 + m))
            {
                break;
            }
        }
        printf("%d\n", answer);
        return;
    }
    if (k == 0)
    {
        std::fill(pos + 1, pos + n + 2, 0);
        for (int i = 1; i <= n; ++i)
        {
            if (p[i])
            {
                pos[p[i]] = i;
            }
        }
        int curr = 0, prev = 1;
        std::fill(dp[curr], dp[curr] + n + 2, 0);
        dp[curr][1] = 1;
        for (int i = 1; i <= n; ++i)
        {
            std::swap(curr, prev);
            std::fill(dp[curr], dp[curr] + n + 2, 0);
            for (int x = 1; x <= i; ++x)
            {
                if (dp[prev][x] == 0)
                {
                    continue;
                }
                if (p[i] == 0 || p[i] == x)
                {
                    dp[curr][i + 1] = (dp[curr][i + 1] + dp[prev][x]) % Mod;
                }
                if ((p[i] == 0 || p[i] == i + 1) && (pos[i + 1] == 0 || pos[i + 1] == i))
                {
                    dp[curr][x] = (dp[curr][x] + dp[prev][x]) % Mod;
                }
                printf("%lld:%lld\n", dp[curr][x], dp[prev][x]);
            }
        }
        printf("%lld\n", dp[curr][n + 1]);
        return;
    }
    printf("0\n");
}

int main()
{
    freopen("sing.in", "r", stdin);
    freopen("sing.out", "w", stdout);
    c[1] = 1;
    for (int i = 2; i <= 8e3; i++)
    {
        c[i] = (2 * c[i - 1] + c[i - 2]) % Mod;
    }
    int t;
    scanf("%d%d", &t, &id);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}