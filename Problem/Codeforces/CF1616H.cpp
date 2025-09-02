#include <algorithm>
#include <cstdio>
#include <vector>
constexpr int MaxN = 2e5 + 5;
constexpr long long Mod = 998'244'353;
class node
{
  public:
    int val;
    node *next[2];
    node()
    {
        val = 0;
        next[0] = nullptr;
        next[1] = nullptr;
    }
};
int n, k;
int p[MaxN];
long long pw[MaxN];
node *root;
std::vector<int> v;
void insert(node *cur, int w)
{
    cur->val++;
    if (w > 30)
    {
        return;
    }
    if (cur->next[v[w]] == nullptr)
    {
        cur->next[v[w]] = new node();
    }
    insert(cur->next[v[w]], w + 1);
}
int val(node *cur)
{
    return cur == nullptr ? 0 : cur->val;
}
long long func(node *x, node *y, int w)
{
    if (x == nullptr && y == nullptr)
    {
        return 1;
    }
    if (x == nullptr)
    {
        return pw[val(y)];
    }
    if (y == nullptr)
    {
        return pw[val(x)];
    }
    if (x == y)
    {
        if (w > 30)
        {
            return pw[val(x)];
        }
        node *lc, *rc;
        lc = x->next[0];
        rc = x->next[1];
        if ((k >> (30 - w)) & 1)
        {
            return func(lc, rc, w + 1);
        }
        else
        {
            return (func(lc, lc, w + 1) + func(rc, rc, w + 1) - 1 + Mod) % Mod;
        }
    }
    else
    {
        if (w > 30)
        {
            return pw[val(x) + val(y)];
        }
        node *lx, *rx, *ly, *ry;
        lx = x->next[0];
        rx = x->next[1];
        ly = y->next[0];
        ry = y->next[1];
        if ((k >> (30 - w)) & 1)
        {
            return func(lx, ry, w + 1) * func(ly, rx, w + 1) % Mod;
        }
        else
        {
            long long result = 0;
            result += (func(lx, ly, w + 1) + func(rx, ry, w + 1) - 1 + Mod) % Mod;
            result += (pw[val(lx)] - 1 + Mod) * (pw[val(rx)] - 1 + Mod) % Mod;
            result += (pw[val(ly)] - 1 + Mod) * (pw[val(ry)] - 1 + Mod) % Mod;
            result %= Mod;
            return result;
        }
    }
}
int main()
{
    root = new node();
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        v.clear();
        scanf("%d", &p[i]);
        for (int j = 0; j <= 30; j++)
        {
            v.push_back(p[i] % 2);
            p[i] /= 2;
        }
        std::reverse(v.begin(), v.end());
        insert(root, 0);
    }
    pw[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        pw[i] = pw[i - 1] * 2 % Mod;
    }
    printf("%lld\n", (func(root, root, 0) - 1 + Mod) % Mod);
    return 0;
}