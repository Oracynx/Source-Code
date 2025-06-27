#include <cstdio>
#include <tuple>
#include <vector>
constexpr int MaxN = 2e6 + 5;
int n, m;
int p[MaxN];
int tree[MaxN];
int first[MaxN];
int second[MaxN];
int answer[MaxN];
std::vector<std::tuple<int, int>> v[MaxN];
void change(int x, int val)
{
    for (; x <= n; x += x & -x)
    {
        tree[x] += val;
    }
}
int query(int x)
{
    int result = 0;
    for (; x >= 1; x -= x & -x)
    {
        result += tree[x];
    }
    return result;
}
int query(int l, int r)
{
    return query(r) - query(l - 1);
}
int main()
{
    scanf("%d%*d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }
    for (int i = 1; i <= m; i++)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        v[r].push_back({l, i});
    }
    for (int r = 1; r <= n; r++)
    {
        if (first[p[r]] != 0)
        {
            change(first[p[r]], -1);
        }
        first[p[r]] = second[p[r]];
        second[p[r]] = r;
        if (first[p[r]] != 0)
        {
            change(first[p[r]], 1);
        }
        for (const auto &[l, id] : v[r])
        {
            answer[id] = query(l, r);
        }
    }
    for (int i = 1; i <= m; i++)
    {
        printf("%d\n", answer[i]);
    }
    return 0;
}