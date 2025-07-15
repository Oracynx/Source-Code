#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
constexpr int MaxN = 1e5 + 5;
class node
{
  public:
    int id;
    int l, r, k;
    friend bool operator<(const node &, const node &);
};
int n, m, b;
int p[MaxN];
int cnt[MaxN];
int tree[MaxN];
int answer[MaxN];
std::vector<int> r;
std::vector<node> v;
bool operator<(const node &x, const node &y)
{
    return x.l / b != y.l / b ? x.l < y.l : x.r == y.r ? false : (x.r < y.r) ^ (x.l / b % 2 == 1);
}
void change(int x, int val)
{
    if (x == 0)
    {
        return;
    }
    for (; x <= n; x += x & -x)
    {
        tree[x] += val;
    }
}
int query(int x)
{
    int res = 0;
    for (; x >= 1; x -= x & -x)
    {
        res += tree[x];
    }
    return res;
}
int query(int l, int r)
{
    return query(r) - query(l - 1);
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
        r.push_back(p[i]);
    }
    std::sort(r.begin(), r.end());
    r.erase(std::unique(r.begin(), r.end()), r.end());
    for (int i = 1; i <= n; i++)
    {
        p[i] = std::lower_bound(r.begin(), r.end(), p[i]) - r.begin() + 1;
    }
    for (int i = 1; i <= m; i++)
    {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        v.push_back({i, l, r, k});
    }
    b = std::max(1.0, n / sqrt(m));
    std::sort(v.begin(), v.end());
    int cl, cr;
    cl = 1;
    cr = 0;
    for (const auto &[id, l, r, k] : v)
    {
        for (; l < cl;)
        {
            cl--;
            change(cnt[p[cl]], -1);
            cnt[p[cl]]++;
            change(cnt[p[cl]], 1);
        }
        for (; cr < r;)
        {
            cr++;
            change(cnt[p[cr]], -1);
            cnt[p[cr]]++;
            change(cnt[p[cr]], 1);
        }
        for (; cl < l;)
        {
            change(cnt[p[cl]], -1);
            cnt[p[cl]]--;
            change(cnt[p[cl]], 1);
            cl++;
        }
        for (; r < cr;)
        {
            change(cnt[p[cr]], -1);
            cnt[p[cr]]--;
            change(cnt[p[cr]], 1);
            cr--;
        }
        int res = -1;
        int kl, kr;
        kl = 1;
        kr = n;
        for (; kl <= kr;)
        {
            int mid = (kl + kr) / 2;
            if (query(1, mid) >= k)
            {
                res = mid;
                kr = mid - 1;
            }
            else
            {
                kl = mid + 1;
            }
        }
        answer[id] = res;
    }
    for (int i = 1; i <= m; i++)
    {
        printf("%d\n", answer[i]);
    }
    return 0;
}