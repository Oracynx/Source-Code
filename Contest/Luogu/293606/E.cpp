#include <algorithm>
#include <cstdio>
#include <numeric>
#include <tuple>
#include <vector>
constexpr int MaxN = 5e3 + 5;
int n, m;
int answer;
int fc[MaxN];
std::vector<std::tuple<int, int, int>> inks;
int find(int u)
{
    return fc[u] == u ? u : fc[u] = find(fc[u]);
}
void merge(int u, int v)
{
    u = find(u);
    v = find(v);
    fc[u] = u == v ? u : v;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        inks.push_back({w, u, v});
    }
    int chunk = n;
    std::iota(fc + 1, fc + 1 + n, 1);
    std::sort(inks.begin(), inks.end());
    for (const auto &[w, u, v] : inks)
    {
        if (find(u) != find(v))
        {
            chunk--;
            answer += w;
            merge(u, v);
        }
    }
    if (chunk != 1)
    {
        printf("orz\n");
    }
    else
    {
        printf("%d\n", answer);
    }
    return 0;
}