#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
constexpr int MaxN = 1e5 + 5;
int n, m, k;
int p[MaxN];
char answer[MaxN];
std::vector<int> g[MaxN];
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    if (n == 2)
    {
        if (k == 1)
        {
            printf("impossible\n");
        }
        else
        {
            printf("%s\n", k == 2 ? "UU" : "PP");
        }
        return 0;
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int a = std::max(k, n - k);
    int b = std::min(k, n - k);
    char ca = k > n - k ? 'U' : 'P';
    char cb = k > n - k ? 'P' : 'U';
    if (a >= 1)
    {
        answer[1] = ca;
        a--;
        for (const auto &v : g[1])
        {
            if (answer[v] != '\0' && a >= 1)
            {
                answer[v] = ca;
                a--;
            }
        }
    }
    if (b >= 1)
    {
        answer[n] = cb;
        b--;
        for (const auto &v : g[n])
        {
            if (answer[v] == '\0' && b >= 1)
            {
                answer[v] = cb;
                b--;
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (answer[i] != '\0')
        {
            continue;
        }
        if (a >= 1)
        {
            answer[i] = ca;
            a--;
        }
        else if (b >= 1)
        {
            answer[i] = cb;
            b--;
        }
    }
    if (a < 0 || b < 0)
    {
        assert(0);
        printf("impossible\n");
    }
    else
    {
        printf("%s\n", answer + 1);
    }
    return 0;
}