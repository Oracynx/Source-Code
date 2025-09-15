#include <algorithm>
#include <cstdio>
#include <vector>
constexpr int MaxN = 1e5 + 5;
constexpr int MaxK = 4;
int n, k;
int p[MaxN];
int mask[MaxN * 4];
int tree[MaxN * 4][1 << MaxK];
int cover[MaxN * 4][1 << MaxK];
long long answer;
std::vector<int> v[MaxN];
void build(int c, int s, int t)
{
    if (s == t)
    {
        tree[c][0] = 1;
        return;
    }
    cover[c][0] = 1;
    int mid = (s + t) / 2;
    build(c * 2, s, mid);
    build(c * 2 + 1, mid + 1, t);
}
void upstream(int c)
{
    for (int i = 0; i < 1 << k; i++)
    {
        tree[c][i] = 0;
    }
    for (int i = 0; i < 1 << k; i++)
    {
        for (int j = 0; j < 1 << k; j++)
        {
            if ((i | j) != i || (mask[c] | j) != mask[c])
            {
                continue;
            }
            int k = i - j;
            tree[c][i] = std::max(tree[c][i], tree[c * 2][k] + tree[c * 2 + 1][k]);
        }
    }
}
void change(int c, int s, int t, int l, int r, int d)
{
    if (l <= s && t <= r)
    {
        if (s == t)
        {
            if (d > 0)
            {
                cover[c][1 << (d - 1)]++;
                if (cover[c][1 << (d - 1)] == 1)
                {
                    for (int i = 0; i < 1 << k; i++)
                    {
                        bool suc = true;
                        for (int j = 0; j < k; j++)
                        {
                            suc &= cover[c][1 << j] >= 1 || ~(i >> j) & 1;
                        }
                        tree[c][i] = suc ? 1 : 0;
                    }
                }
            }
            else if (d < 0)
            {
                cover[c][1 << (-d - 1)]--;
                if (cover[c][1 << (-d - 1)] == 0)
                {
                    for (int i = 0; i < 1 << k; i++)
                    {
                        bool suc = true;
                        for (int j = 0; j < k; j++)
                        {
                            suc &= cover[c][1 << j] >= 1 || ~(i >> j) & 1;
                        }
                        tree[c][i] = suc ? 1 : 0;
                    }
                }
            }
        }
        else
        {
            if (d > 0)
            {
                cover[c][1 << (d - 1)]++;
                if (cover[c][1 << (d - 1)] == 1)
                {
                    mask[c] ^= 1 << (d - 1);
                    upstream(c);
                }
            }
            else if (d < 0)
            {
                cover[c][1 << (-d - 1)]--;
                if (cover[c][1 << (-d - 1)] == 0)
                {
                    mask[c] ^= 1 << (-d - 1);
                    upstream(c);
                }
            }
        }
        return;
    }
    int mid = (s + t) / 2;
    if (l <= mid)
    {
        change(c * 2, s, mid, l, r, d);
    }
    if (r > mid)
    {
        change(c * 2 + 1, mid + 1, t, l, r, d);
    }
    upstream(c);
}
void remove(const std::vector<int> &v)
{
    if (v.empty())
    {
        return;
    }
    int sk = v.size();
    for (int i = 0; i + 1 < sk; i++)
    {
        change(1, 1, n, v[i] + 1, v[i + 1], -(sk - i - 1));
    }
    if (sk <= k)
    {
        change(1, 1, n, 1, v[0], -sk);
    }
}
void add(const std::vector<int> &v)
{
    if (v.empty())
    {
        return;
    }
    int sk = v.size();
    for (int i = 0; i + 1 < sk; i++)
    {
        change(1, 1, n, v[i] + 1, v[i + 1], sk - i - 1);
    }
    if (sk <= k)
    {
        change(1, 1, n, 1, v[0], sk);
    }
}
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }
    build(1, 1, n);
    for (int i = 1; i <= n; i++)
    {
        remove(v[p[i]]);
        v[p[i]].push_back(i);
        if (int(v[p[i]].size()) > k + 1)
        {
            v[p[i]].erase(v[p[i]].begin());
        }
        add(v[p[i]]);
        answer += tree[1][(1 << k) - 1];
    }
    printf("%lld\n", answer);
    return 0;
}