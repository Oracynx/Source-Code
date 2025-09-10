#include <algorithm>
#include <cstdio>
#include <tuple>
#include <vector>
constexpr int MaxN = 1e6 + 5;
int n, m, c;
int last[MaxN];
int answer[MaxN];
int tree[MaxN * 4];
int lazy[MaxN * 4];
bool vis[MaxN];
std::vector<int> un;
std::vector<std::tuple<int, int>> v[MaxN];
int ref(int x)
{
    return std::lower_bound(un.begin(), un.end(), x) - un.begin() + 1;
}
void downsteram(int c)
{
    if (lazy[c] != 0)
    {
        if (answer[lazy[c]] > answer[tree[c * 2]])
        {
            tree[c * 2] = lazy[c];
        }
        if (answer[lazy[c]] > answer[lazy[c * 2]])
        {
            lazy[c * 2] = lazy[c];
        }
        if (answer[lazy[c]] > answer[tree[c * 2 + 1]])
        {
            tree[c * 2 + 1] = lazy[c];
        }
        if (answer[lazy[c]] > answer[lazy[c * 2 + 1]])
        {
            lazy[c * 2 + 1] = lazy[c];
        }
        lazy[c] = 0;
    }
}
void change(int c, int s, int t, int l, int r, int d)
{
    if (l <= s && t <= r)
    {
        if (answer[d] > answer[tree[c]])
        {
            tree[c] = d;
        }
        if (answer[d] > answer[lazy[c]])
        {
            lazy[c] = d;
        }
        return;
    }
    downsteram(c);
    int mid = (s + t) / 2;
    if (l <= mid)
    {
        change(c * 2, s, mid, l, r, d);
    }
    if (r > mid)
    {
        change(c * 2 + 1, mid + 1, t, l, r, d);
    }
    tree[c] = answer[tree[c * 2]] > answer[tree[c * 2 + 1]] ? tree[c * 2] : tree[c * 2 + 1];
}
int query(int c, int s, int t, int l, int r)
{
    if (l <= s && t <= r)
    {
        return tree[c];
    }
    downsteram(c);
    int result = 0;
    int mid = (s + t) / 2;
    if (l <= mid)
    {
        int d = query(c * 2, s, mid, l, r);
        result = answer[d] > answer[result] ? d : result;
    }
    if (r > mid)
    {
        int d = query(c * 2 + 1, mid + 1, t, l, r);
        result = answer[d] > answer[result] ? d : result;
    }
    return result;
}
int main()
{
    scanf("%d%d", &n, &c);
    for (int i = 1; i <= c; i++)
    {
        int k, l, r;
        scanf("%d%d%d", &k, &l, &r);
        un.push_back(l);
        un.push_back(r);
        v[k].push_back({l, r});
    }
    std::sort(un.begin(), un.end());
    un.erase(std::unique(un.begin(), un.end()), un.end());
    m = un.size();
    for (int i = 1; i <= n; i++)
    {
        for (auto &[l, r] : v[i])
        {
            l = ref(l);
            r = ref(r);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        int best = 0;
        for (const auto &[l, r] : v[i])
        {
            int d = query(1, 1, m, l, r);
            best = answer[d] > answer[best] ? d : best;
        }
        last[i] = best;
        answer[i] = answer[last[i]] + 1;
        for (const auto &[l, r] : v[i])
        {
            change(1, 1, m, l, r, i);
        }
    }
    int best = 0;
    for (int i = 1; i <= n; i++)
    {
        best = answer[i] > answer[best] ? i : best;
    }
    printf("%d\n", n - answer[best]);
    int u = best;
    for (;;)
    {
        vis[u] = true;
        u = last[u];
        if (u == 0)
        {
            break;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            printf("%d ", i);
        }
    }
    printf("\n");
    return 0;
}