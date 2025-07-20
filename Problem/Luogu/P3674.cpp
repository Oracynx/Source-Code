#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <vector>
constexpr int MaxN = 1e5 + 5;
class node
{
  public:
    int id;
    int type;
    int l, r;
    int value;
};
int n, m, b;
int p[MaxN];
int cnt[MaxN];
bool answer[MaxN];
std::vector<node> v;
std::bitset<MaxN> d;
std::bitset<MaxN> rd;
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }
    for (int i = 1; i <= m; i++)
    {
        int op, l, r, x;
        scanf("%d%d%d%d", &op, &l, &r, &x);
        v.push_back({i, op, l, r, x});
    }
    b = n / sqrt(m);
    std::sort(v.begin(), v.end(), [](const node &x, const node &y) -> bool {
        return x.l / b != y.l / b ? x.l < y.l : x.r == y.r ? false : (x.r < y.r) ^ (x.l / b % 2 == 1);
    });
    int cl, cr;
    cl = 1;
    cr = 0;
    for (const auto &[id, type, l, r, value] : v)
    {
        for (; l < cl;)
        {
            cl--;
            if (cnt[p[cl]] == 0)
            {
                d[p[cl]] = true;
                rd[1e5 - p[cl]] = true;
            }
            cnt[p[cl]]++;
        }
        for (; cr < r;)
        {
            cr++;
            if (cnt[p[cr]] == 0)
            {
                d[p[cr]] = true;
                rd[1e5 - p[cr]] = true;
            }
            cnt[p[cr]]++;
        }
        for (; cl < l;)
        {
            if (cnt[p[cl]] == 1)
            {
                d[p[cl]] = false;
                rd[1e5 - p[cl]] = false;
            }
            cnt[p[cl]]--;
            cl++;
        }
        for (; r < cr;)
        {
            if (cnt[p[cr]] == 1)
            {
                d[p[cr]] = false;
                rd[1e5 - p[cr]] = false;
            }
            cnt[p[cr]]--;
            cr--;
        }
        if (type == 1)
        {
            answer[id] = ((d << value) & d).count() >= 1 || ((d >> value) & d).count() >= 1;
        }
        else if (type == 2)
        {
            answer[id] = ((rd >> (1e5 - value)) & d).count() >= 1;
        }
        else if (type == 3)
        {
            for (int i = 1; i * i <= value; i++)
            {
                if (value % i != 0)
                {
                    continue;
                }
                int x, y;
                x = i;
                y = value / i;
                if (cnt[x] >= 1 && cnt[y] >= 1)
                {
                    answer[id] = true;
                    break;
                }
            }
        }
    }
    for (int i = 1; i <= m; i++)
    {
        printf("%s\n", answer[i] ? "hana" : "bi");
    }
    return 0;
}