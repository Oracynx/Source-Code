#include <algorithm>
#include <cctype>
#include <cstdio>
#include <set>
#include <vector>
constexpr int MaxN = 1e6 + 5;
int n, m;
int k, c;
int answer;
int under[MaxN];
bool have[MaxN];
std::vector<int> g[MaxN];
void dfsInit(int u, int f)
{
    under[u] = -1;
    if (have[u])
    {
        under[u] = 0;
    }
    for (const auto &v : g[u])
    {
        if (v == f)
        {
            continue;
        }
        dfsInit(v, u);
        under[u] = std::max(under[u], under[v] == -1 ? -1 : under[v] + 1);
    }
}
void dfsCalc(int u, int f, int upper, int len)
{
    std::multiset<int> set;
    for (const auto &v : g[u])
    {
        if (v == f)
        {
            continue;
        }
        set.insert(under[v]);
    }
    int d = set.empty() ? -1 : *set.rbegin() + 1;
    d -= len;
    d -= k;
    d = std::max(0, d);
    d++;
    d = std::max(d, -1);
    int cp = upper;
    cp -= k;
    cp = std::max(cp, 0);
    answer = std::min(answer, std::max({len + d, len + cp}));
    for (const auto &v : g[u])
    {
        if (v == f)
        {
            continue;
        }
        set.erase(set.find(under[v]));
        dfsCalc(v, u, std::max(set.empty() || *set.rbegin() == -1 ? -1 : std::max(*set.rbegin() + 1 - len, -1), upper),
                len + 1);
        set.insert(under[v]);
    }
}
void read(int &x)
{
    x = 0;
    bool f = false;
    char ch = '\0';
    for (; !std::isdigit(ch);)
    {
        ch = getchar();
        if (ch == '-')
        {
            f = true;
        }
    }
    for (; isdigit(ch);)
    {
        x = x * 10 + (ch ^ 48);
        ch = getchar();
    }
    x = f ? -x : x;
}
int main()
{
    read(n);
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        read(u);
        read(v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    read(m);
    for (int i = 1; i <= m; i++)
    {
        int x;
        read(x);
        have[x] = true;
    }
    read(k);
    read(c);
    dfsInit(c, 0);
    answer = 0x3f3f3f3f;
    dfsCalc(c, 0, -1, 0);
    printf("%d\n", answer);
    return 0;
}