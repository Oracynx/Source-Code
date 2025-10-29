#include <algorithm>
#include <cstdio>
constexpr int MaxN = 1e5 + 5;
class node
{
  public:
    double tree;
    double all;
    double left;
    double right;
    node()
    {
        tree = 0;
        all = 0;
        left = 0;
        right = 0;
    }
    node(double x)
    {
        tree = std::max(0.0, x);
        all = x;
        left = std::max(0.0, x);
        right = std::max(0.0, x);
    }
    node upstream(const node &a, const node &b)
    {
        node c;
        c.tree = std::max({0.0, a.tree, b.tree, a.right + b.left});
        c.all = a.all + b.all;
        c.left = std::max(a.left, a.all + b.left);
        c.right = std::max(a.right + b.all, b.right);
        return (*this) = c;
    }
};
int n, m, c;
int x[MaxN];
int p[MaxN];
double answer;
double ex[MaxN];
node tree[MaxN * 4];
void build(int c, int s, int t)
{
    if (s == t)
    {
        tree[c] = node(ex[s]);
        return;
    }
    int mid = (s + t) / 2;
    build(c * 2, s, mid);
    build(c * 2 + 1, mid + 1, t);
    tree[c].upstream(tree[c * 2], tree[c * 2 + 1]);
}
node query(int c, int s, int t, int l, int r)
{
    if (l <= s && t <= r)
    {
        return tree[c];
    }
    int mid = (s + t) / 2;
    if (l <= mid && r > mid)
    {
        return node().upstream(query(c * 2, s, mid, l, r), query(c * 2 + 1, mid + 1, t, l, r));
    }
    else if (l <= mid)
    {
        return query(c * 2, s, mid, l, r);
    }
    else if (r > mid)
    {
        return query(c * 2 + 1, mid + 1, t, l, r);
    }
    return node();
}
int main()
{
    scanf("%d%d%d", &n, &m, &c);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &x[i]);
    }
    for (int i = 1; i <= n - 1; i++)
    {
        scanf("%d", &p[i]);
        ex[i] = (x[i + 1] - x[i]) / 2.0 - p[i] / 100.0 * c;
    }
    build(1, 1, n - 1);
    for (int i = 1; i <= m; i++)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        answer += l == r ? 0 : query(1, 1, n - 1, l, r - 1).tree;
    }
    printf("%.6lf\n", answer);
    return 0;
}