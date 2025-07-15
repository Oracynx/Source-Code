#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
constexpr int MaxN = 1e5 + 5;
class node
{
  public:
    int id;
    int l, r;
    int a, b;
};
int n, m, b;
int p[MaxN];
int cnt[MaxN];
long long tree[2][MaxN];
long long answer[2][MaxN];
std::vector<node> v;
void change(int u, int x, long long val)
{
    for (; x <= n; x += x & -x)
    {
        tree[u][x] += val;
    }
}
long long query(int u, int x)
{
    long long result = 0;
    for (; x >= 1; x -= x & -x)
    {
        result += tree[u][x];
    }
    return result;
}
long long query(int u, int l, int r)
{
    return query(u, r) - query(u, l - 1);
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }
    for (int i = 1; i <= m; i++)
    {
        int l, r, a, b;
        scanf("%d%d%d%d", &l, &r, &a, &b);
        v.push_back({i, l, r, a, b});
    }
    b = std::max(1.0, n / sqrt(m));
    std::sort(v.begin(), v.end(), [](const node &x, const node &y) -> bool {
        return x.l / b != y.l / b ? x.l < y.l : x.r == y.r ? false : (x.r < y.r) ^ (x.l / b % 2 == 1);
    });
    int cl, cr;
    cl = 1;
    cr = 0;
    for (const auto &[id, l, r, a, b] : v)
    {
        for (; l < cl;)
        {
            cl--;
            change(0, p[cl], 1);
            if (cnt[p[cl]] == 0)
            {
                change(1, p[cl], 1);
            }
            cnt[p[cl]]++;
        }
        for (; cr < r;)
        {
            cr++;
            change(0, p[cr], 1);
            if (cnt[p[cr]] == 0)
            {
                change(1, p[cr], 1);
            }
            cnt[p[cr]]++;
        }
        for (; cl < l;)
        {
            change(0, p[cl], -1);
            if (cnt[p[cl]] == 1)
            {
                change(1, p[cl], -1);
            }
            cnt[p[cl]]--;
            cl++;
        }
        for (; r < cr;)
        {
            change(0, p[cr], -1);
            if (cnt[p[cr]] == 1)
            {
                change(1, p[cr], -1);
            }
            cnt[p[cr]]--;
            cr--;
        }
        answer[0][id] = query(0, a, b);
        answer[1][id] = query(1, a, b);
    }
    for (int i = 1; i <= m; i++)
    {
        printf("%lld %lld\n", answer[0][i], answer[1][i]);
    }
    return 0;
}