#include <algorithm>
#include <cstdio>
#include <tuple>
#include <vector>
constexpr int MaxN = 1e2 + 5;
constexpr long long Mod = 998'244'353;
int n;
int p[MaxN];
bool vis[MaxN];
long long answer[MaxN];
std::vector<std::tuple<int, int>> v;
void check()
{
    std::vector<long long> r;
    for (const auto &[x, y] : v)
    {
        r.push_back(p[x] + p[y]);
    }
    std::sort(r.begin(), r.end());
    for (int i = 1; i <= n; i++)
    {
        answer[i] += r[i - 1];
        answer[i] %= Mod;
    }
}
void dfs(int u)
{
    if (u > n)
    {
        check();
        return;
    }
    int x = 1;
    for (; vis[x];)
    {
        x++;
    }
    vis[x] = true;
    for (int y = x + 1; y <= 2 * n; y++)
    {
        if (vis[y])
        {
            continue;
        }
        vis[y] = true;
        v.push_back({x, y});
        dfs(u + 1);
        v.pop_back();
        vis[y] = false;
    }
    vis[x] = false;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= 2 * n; i++)
    {
        scanf("%d", &p[i]);
    }
    dfs(1);
    for (int i = 1; i <= n; i++)
    {
        printf("%lld ", answer[i]);
    }
    printf("\n");
    return 0;
}