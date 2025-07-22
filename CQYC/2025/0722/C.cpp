#include <cstdio>
#include <vector>
constexpr int MaxN = 1e2 + 5;
constexpr int MaxM = 1e4 + 5;
int n, m;
int a[MaxN];
int b[MaxN];
int best[MaxM];
int plan[MaxM];
bool near[MaxN][MaxN];
int A(const std::vector<int> &v)
{
    int result = 0;
    for (const auto &val : v)
    {
        result += a[val];
    }
    return result;
}
int B(const std::vector<int> &v)
{
    int result = 0;
    for (const auto &val : v)
    {
        result += b[val];
    }
    return result;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &a[i], &b[i]);
    }
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        near[u][v] = true;
        near[v][u] = true;
    }
    for (int j = 1; j < 1 << n; j++)
    {
        std::vector<int> v;
        for (int i = 1; i <= n; i++)
        {
            if ((j >> (i - 1)) & 1)
            {
                v.push_back(i);
            }
        }
        bool skip = false;
        for (int i = 0; i < int(v.size()) && !skip; i++)
        {
            for (int j = i + 1; j < int(v.size()) && !skip; j++)
            {
                if (near[v[i]][v[j]])
                {
                    skip = true;
                }
            }
        }
        if (skip)
        {
            continue;
        }
        int x = A(v);
        if (!(1 <= x && x <= m))
        {
            continue;
        }
        int fb = B(v);
        if (best[x] < fb)
        {
            best[x] = fb;
            plan[x] = 0;
        }
        if (best[x] == fb)
        {
            plan[x]++;
        }
    }
    for (int i = 1; i <= m; i++)
    {
        printf("%d ", plan[i]);
    }
    printf("\n");
    return 0;
}