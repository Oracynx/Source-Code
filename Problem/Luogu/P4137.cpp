#include <algorithm>
#include <cstdio>
#include <tuple>
#include <vector>
constexpr int MaxN = 3e5 + 5;
int n, m;
int p[MaxN];
int tree[MaxN * 4];
int answer[MaxN];
std::vector<std::tuple<int, int>> v[MaxN];
void change(int c, int s, int t, int w, int val)
{
    if (s == t)
    {
        tree[c] = val;
        return;
    }
    int mid = (s + t) / 2;
    if (w <= mid)
    {
        change(c * 2, s, mid, w, val);
    }
    else
    {
        change(c * 2 + 1, mid + 1, t, w, val);
    }
    tree[c] = std::min(tree[c * 2], tree[c * 2 + 1]);
}
int query(int c, int s, int t, int l)
{
    if (s == t)
    {
        return s;
    }
    int mid = (s + t) / 2;
    if (tree[c * 2] < l)
    {
        return query(c * 2, s, mid, l);
    }
    else
    {
        return query(c * 2 + 1, mid + 1, t, l);
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
        p[i]++;
    }
    for (int i = 1; i <= m; i++)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        v[r].push_back({l, i});
    }
    for (int r = 1; r <= n; r++)
    {
        change(1, 1, 3e5, p[r], r);
        for (const auto &[l, id] : v[r])
        {
            answer[id] = query(1, 1, 3e5, l) - 1;
        }
    }
    for (int i = 1; i <= m; i++)
    {
        printf("%d\n", answer[i]);
    }
    return 0;
}