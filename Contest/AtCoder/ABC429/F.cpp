#include <algorithm>
#include <cstdio>
class node
{
  public:
    int cross[3][3];
    node()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cross[i][j] = 0x3f3f3f3f;
            }
        }
    }
    node merge(const node &a, const node &b)
    {
        node res;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    res.cross[i][j] = std::min(res.cross[i][j], a.cross[i][k] + b.cross[k][j] + 1);
                }
            }
        }
        return (*this) = res;
    }
};
constexpr int MaxN = 2e5 + 5;
int n, m;
char map[3][MaxN];
node tree[MaxN * 4];
void build(int c, int s, int t)
{
    if (s == t)
    {
        for (int i = 0; i < 3; i++)
        {
            tree[c].cross[i][i] = map[i][s] == '.' ? 0 : 0x3f3f3f3f;
        }
        for (int i = 0; i < 2; i++)
        {
            if (map[i][s] == '.' && map[i + 1][s] == '.')
            {
                tree[c].cross[i][i + 1] = 1;
                tree[c].cross[i + 1][i] = 1;
            }
        }
        if (map[0][s] == '.' && map[1][s] == '.' && map[2][s] == '.')
        {
            tree[c].cross[0][2] = 2;
            tree[c].cross[2][0] = 2;
        }
        return;
    }
    int mid = (s + t) / 2;
    build(c * 2, s, mid);
    build(c * 2 + 1, mid + 1, t);
    tree[c].merge(tree[c * 2], tree[c * 2 + 1]);
}
void reupdate(int c, int s, int t, int w)
{
    if (s == t)
    {
        tree[c] = node();
        for (int i = 0; i < 3; i++)
        {
            tree[c].cross[i][i] = map[i][s] == '.' ? 0 : 0x3f3f3f3f;
        }
        for (int i = 0; i < 2; i++)
        {
            if (map[i][s] == '.' && map[i + 1][s] == '.')
            {
                tree[c].cross[i][i + 1] = 1;
                tree[c].cross[i + 1][i] = 1;
            }
        }
        if (map[0][s] == '.' && map[1][s] == '.' && map[2][s] == '.')
        {
            tree[c].cross[0][2] = 2;
            tree[c].cross[2][0] = 2;
        }
        return;
    }
    int mid = (s + t) / 2;
    if (w <= mid)
    {
        reupdate(c * 2, s, mid, w);
    }
    else
    {
        reupdate(c * 2 + 1, mid + 1, t, w);
    }
    tree[c].merge(tree[c * 2], tree[c * 2 + 1]);
}
int query()
{
    return tree[1].cross[0][2] == 0x3f3f3f3f ? -1 : tree[1].cross[0][2];
}
int main()
{
    scanf("%d", &n);
    for (int i = 0; i < 3; i++)
    {
        scanf("%s", map[i] + 1);
    }
    build(1, 1, n);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
        int r, c;
        scanf("%d%d", &r, &c);
        r--;
        map[r][c] = map[r][c] == '.' ? '#' : '.';
        reupdate(1, 1, n, c);
        printf("%d\n", query());
    }
    return 0;
}