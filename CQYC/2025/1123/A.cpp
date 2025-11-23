#include <algorithm>
#include <cassert>
#include <cstdio>
#include <numeric>
#include <utility>
constexpr int MaxN = 2e5 + 5;
class node
{
  public:
    int x;
    int c;
    int lazy;
    node()
    {
        x = 0;
        c = 0;
        lazy = 0;
    }
    node upstream(const node &a, const node &b)
    {
        node r;
        r.x = std::min(a.x, b.x);
        r.c = a.x <= b.x ? a.c : b.c;
        return (*this) = r;
    }
    void makeTag(int w)
    {
        x += w;
        lazy += w;
    }
};
int n;
int p[MaxN];
int answer[MaxN];
node tree[MaxN * 4];
void downstream(int c)
{
    if (tree[c].lazy)
    {
        tree[c * 2].makeTag(tree[c].lazy);
        tree[c * 2 + 1].makeTag(tree[c].lazy);
        tree[c].lazy = 0;
    }
}
void build(int c, int s, int t)
{
    if (s == t)
    {
        tree[c].x = p[s];
        tree[c].c = s;
        return;
    }
    int mid = (s + t) / 2;
    build(c * 2, s, mid);
    build(c * 2 + 1, mid + 1, t);
    tree[c].upstream(tree[c * 2], tree[c * 2 + 1]);
}
void change(int c, int s, int t, int l, int r, int w)
{
    assert(l <= r);
    if (l <= s && t <= r)
    {
        tree[c].makeTag(w);
        return;
    }
    downstream(c);
    int mid = (s + t) / 2;
    if (l <= mid)
    {
        change(c * 2, s, mid, l, r, w);
    }
    if (r > mid)
    {
        change(c * 2 + 1, mid + 1, t, l, r, w);
    }
    tree[c].upstream(tree[c * 2], tree[c * 2 + 1]);
}
node query(int c, int s, int t, int l, int r)
{
    if (l <= s && t <= r)
    {
        return tree[c];
    }
    downstream(c);
    int mid = (s + t) / 2;
    if (l <= mid && r > mid)
    {
        return node().upstream(query(c * 2, s, mid, l, r), query(c * 2 + 1, mid + 1, t, l, r));
    }
    else if (l <= mid)
    {
        return query(c * 2, s, mid, l, r);
    }
    else
    {
        return query(c * 2 + 1, mid + 1, t, l, r);
    }
}
void take(int u, int v)
{
    std::swap(answer[u], answer[v]);
    change(1, 1, n, u, v - 1, -1);
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n - 1; i++)
    {
        scanf("%d", &p[i]);
        if (p[i] % 2 == 1)
        {
            printf("No\n");
            return 0;
        }
        p[i] /= 2;
    }
    build(1, 1, n);
    std::iota(answer + 1, answer + 1 + n, 1);
    for (int i = 1; i <= n - 1; i++)
    {
        node cur = query(1, 1, n, i, i);
        if (cur.x != 1 || answer[i] != i)
        {
            if (cur.x != 0)
            {
                printf("No\n");
                return 0;
            }
            continue;
        }
        node last = query(1, 1, n, i, n);
        if (last.x >= 1)
        {
            take(i, n);
        }
        else
        {
            take(i, last.c);
        }
    }
    printf("Yes\n");
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", answer[i]);
    }
    printf("\n");
    return 0;
}