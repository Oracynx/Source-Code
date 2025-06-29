#include <algorithm>
#include <cstdio>
#include <numeric>
#include <unordered_map>
#include <utility>
constexpr int MaxN = 12;
int n, m;
int answer;
int f[MaxN];
unsigned long long base;
std::unordered_map<unsigned long long, bool> vis;
int getId(int u, int v)
{
    u--;
    v--;
    if (u > v)
    {
        std::swap(u, v);
    }
    return u * (2 * n - 1 - u) / 2 + (v - u - 1);
}
int popcount(unsigned long long x)
{
    int result = 0;
    for (; x != 0;)
    {
        if (x & 1)
        {
            result++;
        }
        x >>= 1;
    }
    return result;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        int id = getId(u, v);
        base |= 1ull << id;
    }
    std::iota(f + 1, f + 1 + n, 1);
    for (;;)
    {
        bool suc = true;
        for (int i = 1; i <= n; i++)
        {
            if (f[i] == i || f[f[i]] == i)
            {
                suc = false;
                break;
            }
        }
        if (suc)
        {
            unsigned long long now = 0;
            for (int i = 1; i <= n; i++)
            {
                int id = getId(i, f[i]);
                now |= 1ull << id;
            }
            if (!vis[now])
            {
                vis[now] = true;
                answer = std::max(answer, popcount(now & base));
            }
        }
        if (!std::next_permutation(f + 1, f + 1 + n))
        {
            break;
        }
    }
    printf("%d\n", m + n - 2 * answer);
    return 0;
}