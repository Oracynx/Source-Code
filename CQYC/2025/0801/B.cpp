#include <algorithm>
#include <cstdio>
#include <map>
#include <set>
#include <tuple>
#include <vector>
constexpr int MaxN = 5e4 + 5;
int n, k;
int answer;
int in[MaxN];
int have[MaxN];
bool vis[MaxN];
std::map<int, bool> g[MaxN];
std::set<std::tuple<int, int>> set;
int popcount(int x)
{
    return x == 0 ? 0 : (x & 1) + popcount(x >> 1);
}
int calc(const std::vector<int> &s)
{
    int n = s.size();
    for (int i = 0; i < n; i++)
    {
        have[i] = 1 << i;
        for (int j = 0; j < n; j++)
        {
            if (g[s[i]].count(s[j]) >= 1)
            {
                have[i] |= 1 << j;
            }
        }
    }
    int result = 0;
    for (int j = 0; j < 1 << n; j++)
    {
        int status = j;
        for (int i = 0; i < n; i++)
        {
            if ((j >> i) & 1)
            {
                status &= have[i];
            }
        }
        if (status == j)
        {
            result = std::max(result, popcount(j));
        }
    }
    return result;
}
int main()
{
    scanf("%d%d", &n, &k);
    for (int u = 1; u <= n; u++)
    {
        int c;
        scanf("%d", &c);
        for (int j = 1; j <= c; j++)
        {
            int v;
            scanf("%d", &v);
            v++;
            g[u][v] = true;
            in[u]++;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        set.insert({in[i], i});
    }
    for (; !set.empty();)
    {
        const auto [_a, u] = *set.begin();
        set.erase(set.begin());
        std::vector<int> s;
        s.push_back(u);
        for (const auto &[v, is] : g[u])
        {
            if (vis[v] || !is)
            {
                continue;
            }
            s.push_back(v);
        }
        answer = std::max(answer, calc(s));
        vis[u] = true;
        for (const auto &[v, is] : g[u])
        {
            if (vis[v] || !is)
            {
                continue;
            }
            set.erase({in[v], v});
            in[v]--;
            set.insert({in[v], v});
        }
    }
    printf("%d\n", answer);
    return 0;
}