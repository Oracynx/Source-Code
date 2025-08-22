#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>
constexpr int MaxN = 1e2 + 5;
int n;
int m[MaxN];
char s[MaxN][MaxN];
bool make(int u, int x)
{
    std::sort(s[u] + 1, s[u] + 1 + m[u]);
    for (int i = 1; i <= x; i++)
    {
        int next = -1;
        for (int j = i; j <= m[u]; j++)
        {
            if (s[u][j] == s[u - 1][i])
            {
                next = j;
                break;
            }
        }
        if (next == -1)
        {
            return false;
        }
        std::swap(s[u][next], s[u][i]);
    }
    if (x == m[u] || x == m[u - 1])
    {
        std::sort(s[u] + 1 + x, s[u] + 1 + m[u]);
        return true;
    }
    int next = -1;
    for (int i = x + 1; i <= m[u]; i++)
    {
        if (s[u][i] > s[u - 1][x + 1])
        {
            if (next == -1 || s[u][i] < s[u][next])
            {
                next = i;
            }
        }
    }
    if (next == -1)
    {
        return false;
    }
    std::swap(s[u][x + 1], s[u][next]);
    std::sort(s[u] + 2 + x, s[u] + 1 + m[u]);
    return true;
}
void solve()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", s[i] + 1);
        m[i] = strlen(s[i] + 1);
        std::sort(s[i] + 1, s[i] + 1 + m[i]);
    }
    for (int i = 2; i <= n; i++)
    {
        int result = -1;
        for (int j = 0; j <= std::min(m[i] - 1, m[i - 1]); j++)
        {
            if (make(i, j))
            {
                result = j;
            }
        }
        if (m[i] >= m[i - 1] && make(i, m[i - 1]))
        {
            result = m[i - 1];
        }
        if (result == -1)
        {
            printf("No\n");
            return;
        }
        make(i, result);
    }
    printf("Yes\n");
    for (int i = 1; i <= n; i++)
    {
        printf("%s ", s[i] + 1);
    }
    printf("\n");
}
int main()
{
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);
    int t;
    scanf("%*d%d", &t);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}