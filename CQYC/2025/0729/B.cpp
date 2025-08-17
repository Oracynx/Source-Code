#include <cstdio>
#include <set>
#include <vector>
constexpr int MaxN = 1e6 + 5;
int n, q;
std::vector<int> g[MaxN];
std::vector<int> pruefer_code()
{
    std::set<int> leafs;
    std::vector<int> degree(n);
    std::vector<bool> killed(n);
    for (int i = 0; i < n; i++)
    {
        degree[i] = g[i].size();
        if (degree[i] == 1)
            leafs.insert(i);
    }

    std::vector<int> code(n - 2);
    for (int i = 0; i < n - 2; i++)
    {
        int leaf = *leafs.begin();
        leafs.erase(leafs.begin());
        killed[leaf] = true;
        int v;
        for (int u : g[leaf])
            if (!killed[u])
                v = u;
        code[i] = v;
        if (--degree[v] == 1)
            leafs.insert(v);
    }
    return code;
}
int main()
{
    scanf("%d%d", &n, &q);
    n = (1 << n) - 1;
    for (int i = 2; i <= n; i++)
    {
        g[i - 1].push_back(i / 2 - 1);
        g[i / 2 - 1].push_back(i - 1);
    }
    auto prufer = pruefer_code();
    for (int i = 1; i <= q; i++)
    {
        int k, d, m;
        scanf("%d%d%d", &k, &d, &m);
        long long answer = 0;
        for (int j = 0; j < m; j++)
        {
            answer += prufer[(k + j * d - 1 + n - 2) % (n - 2)] + 1;
        }
        printf("%lld\n", answer);
    }
    return 0;
}