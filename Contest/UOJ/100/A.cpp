#include <algorithm>
#include <cstdio>
#include <tuple>
#include <vector>
constexpr int MaxN = 2e6 + 5;
int c;
int n;
int cnt[MaxN];
char s[MaxN];
bool can[MaxN];
bool light[MaxN];
std::vector<int> answer;
std::vector<int> v[MaxN];
std::vector<int> g[MaxN];
std::vector<int> vl[MaxN];
std::vector<std::tuple<int, int>> vg[MaxN];
void solveSpA()
{
    for (int i = 1; i <= n; i++)
    {
        if (s[i] == '0' ^ i % 2 == 0)
        {
            printf("NO\n");
            return;
        }
    }
    printf("YES\n");
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", i);
    }
    printf("\n");
}
void dfsInit(int u, int f)
{
    cnt[u] = light[u] ? 1 : 0;
    for (const auto &v : g[u])
    {
        if (v == f)
        {
            continue;
        }
        dfsInit(v, u);
        cnt[u] += cnt[v];
    }
}
bool dfsCheck(int u, int f, int bef, int want)
{
    if (bef == want)
    {
        return true;
    }
    if (bef > want)
    {
        return false;
    }
    bef += light[u] ? 1 : 0;
    int all = cnt[u] - (light[u] ? 1 : 0);
    for (const auto &v : g[u])
    {
        if (v == f)
        {
            continue;
        }
        if (dfsCheck(v, u, bef + all - cnt[v], want))
        {
            return true;
        }
    }
    return false;
}
int near(const std::vector<int> &from, const std::vector<int> &to)
{
    if (from.size() + 1 != to.size())
    {
        return -1;
    }
    int result = -1;
    auto it = from.begin();
    for (const auto &val : to)
    {
        if (it == from.end() || val != *it)
        {
            if (result == -1)
            {
                result = val;
            }
            else
            {
                return -1;
            }
        }
        else
        {
            it++;
        }
    }
    return result;
}
bool check(int have)
{
    if (have % 2 == 1)
    {
        return false;
    }
    dfsInit(1, 0);
    return dfsCheck(1, 0, 0, have / 2);
}
bool findAnswer(int u, int d)
{
    if (((s[d] == '0') ^ can[u]) && d != 0)
    {
        return false;
    }
    if (d == n)
    {
        return true;
    }
    for (const auto &[v, w] : vg[u])
    {
        if (findAnswer(v, d + 1))
        {
            answer.push_back(w);
            return true;
        }
    }
    return false;
}
void solve()
{
    scanf("%d", &n);
    vl[0].clear();
    for (int i = 1; i <= n; i++)
    {
        g[i].clear();
        vl[i].clear();
        light[i] = false;
    }
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    scanf(" %s", s + 1);
    if (c == 4)
    {
        solveSpA();
        return;
    }
    for (int j = 0; j < 1 << n; j++)
    {
        v[j].clear();
        vg[j].clear();
        int have = 0;
        for (int i = 1; i <= n; i++)
        {
            if ((j >> (i - 1l)) & 1)
            {
                have++;
                light[i] = true;
                v[j].push_back(i);
            }
            else
            {
                light[i] = false;
            }
        }
        vl[have].push_back(j);
        can[j] = check(have);
    }
    for (int i = 0; i < n; i++)
    {
        for (const auto &x : vl[i])
        {
            for (const auto &y : vl[i + 1])
            {
                int res = near(v[x], v[y]);
                if (res != -1)
                {
                    vg[x].push_back({y, res});
                }
            }
        }
    }
    answer.clear();
    if (findAnswer(0, 0))
    {
        printf("YES\n");
        std::reverse(answer.begin(), answer.end());
        for (const auto &val : answer)
        {
            printf("%d ", val);
        }
        printf("\n");
    }
    else
    {
        printf("NO\n");
    }
}
int main()
{
    int t;
    scanf("%d%d", &t, &c);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}