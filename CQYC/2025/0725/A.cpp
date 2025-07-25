#include <algorithm>
#include <cctype>
#include <cstdio>
#include <map>
#include <tuple>
#include <vector>
constexpr int MaxN = 1e6 + 5;
constexpr int MaxM = 1e4 + 5;
bool mode;
int n, m, q;
int p[MaxN];
int u[MaxN];
int v[MaxN];
int vis[MaxN];
int cannotA[MaxM][MaxM];
std::vector<int> g[MaxN];
std::map<std::tuple<int, int>, bool> have;
std::map<std::tuple<int, int>, bool> cannotB;
template <typename _Tp> void read(_Tp &x)
{
    x = 0;
    bool f = false;
    char ch = '\0';
    for (;;)
    {
        ch = getchar();
        if (std::isdigit(ch))
        {
            x = ch ^ 48;
            break;
        }
        else if (ch == '-')
        {
            f = true;
        }
    }
    for (;;)
    {
        ch = getchar();
        if (!isdigit(ch))
        {
            break;
        }
        x = x * 10 + (ch ^ 48);
    }
    x = f ? -x : x;
}
void reset()
{
    if (mode)
    {
    }
    else
    {
        cannotB.clear();
    }
}
void make(int u, int v, int flag)
{
    if (mode)
    {
        cannotA[u][v] = flag;
        cannotA[v][u] = flag;
    }
    else
    {
        cannotB[{u, v}] = true;
        cannotB[{v, u}] = true;
    }
}
bool check(int u, int v, int flag)
{
    if (mode)
    {
        return cannotA[u][v] == flag;
    }
    else
    {
        return cannotB[{u, v}];
    }
}
long long dfs(int u, int flag)
{
    vis[u] = flag;
    long long result = p[u];
    for (const auto &v : g[u])
    {
        if (vis[v] == flag || check(u, v, flag))
        {
            continue;
        }
        result += dfs(v, flag);
    }
    return result;
}
int main()
{
    read(n);
    read(m);
    mode = n <= 1e4;
    for (int i = 1; i <= n; i++)
    {
        read(p[i]);
    }
    for (int i = 1; i <= m; i++)
    {
        read(u[i]);
        read(v[i]);
        if (have[{u[i], v[i]}] || u[i] == v[i])
        {
            continue;
        }
        have[{u[i], v[i]}] = true;
        g[u[i]].push_back(v[i]);
        g[v[i]].push_back(u[i]);
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; i++)
    {
        int k;
        read(k);
        reset();
        for (int j = 1; j <= k; j++)
        {
            int x;
            read(x);
            make(u[x], v[x], i);
        }
        long long answer = 0x7f7f7f7f'7f7f7f7f;
        for (int j = 1; j <= n; j++)
        {
            if (vis[j] != i)
            {
                answer = std::min(answer, dfs(j, i));
            }
        }
        printf("%lld\n", answer);
    }
    return 0;
}