#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
constexpr int MaxN = 1e5 + 5;
class node
{
  public:
    static int block;
    int id;
    int l, r, k;
    node()
    {
        id = 0;
        l = r = k = 0;
    }
    node(int _id, int _l, int _r, int _k)
    {
        id = _id;
        l = _l;
        r = _r;
        k = _k;
    }
    friend bool operator<(const node &x, const node &y)
    {
        return x.l / block != y.l / block ? x.l < y.l : x.r == y.r ? false : x.r < y.r ^ x.l / block % 2 == 1;
    }
};
int node::block = 0;
int n, m;
int p[MaxN];
int w[MaxN];
int id[MaxN];
int cnt[MaxN];
int size[MaxN];
int tree[MaxN];
int answer[MaxN];
std::vector<int> g[MaxN];
std::vector<node> v;
void change(int u, int d)
{
    if (u <= 0)
    {
        return;
    }
    for (; u <= n; u += u & -u)
    {
        tree[u] += d;
    }
}
int query(int u)
{
    if (u <= 0)
    {
        return 0;
    }
    int result = 0;
    for (; u >= 1; u -= u & -u)
    {
        result += tree[u];
    }
    return result;
}
int query(int l, int r)
{
    return query(r) - query(l - 1);
}
void dfs(int u, int f)
{
    static int index = 0;
    id[u] = ++index;
    size[u] = 1;
    for (const auto &v : g[u])
    {
        if (v == f)
        {
            continue;
        }
        dfs(v, u);
        size[u] += size[v];
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++)
    {
        w[id[i]] = p[i];
    }
    for (int i = 1; i <= m; i++)
    {
        int u, k;
        scanf("%d%d", &u, &k);
        k = std::min(k, n);
        v.push_back({i, id[u], id[u] + size[u] - 1, k});
    }
    node::block = std::max(1.0, n / sqrt(m));
    std::sort(v.begin(), v.end());
    int cl, cr;
    cl = 1;
    cr = 0;
    for (const auto &[id, l, r, k] : v)
    {
        for (; l < cl;)
        {
            cl--;
            change(cnt[w[cl]], -1);
            cnt[w[cl]]++;
            change(cnt[w[cl]], 1);
        }
        for (; cr < r;)
        {
            cr++;
            change(cnt[w[cr]], -1);
            cnt[w[cr]]++;
            change(cnt[w[cr]], 1);
        }
        for (; cl < l;)
        {
            change(cnt[w[cl]], -1);
            cnt[w[cl]]--;
            change(cnt[w[cl]], 1);
            cl++;
        }
        for (; r < cr;)
        {
            change(cnt[w[cr]], -1);
            cnt[w[cr]]--;
            change(cnt[w[cr]], 1);
            cr--;
        }
        answer[id] = query(k, n);
    }
    for (int i = 1; i <= m; i++)
    {
        printf("%d\n", answer[i]);
    }
    return 0;
}