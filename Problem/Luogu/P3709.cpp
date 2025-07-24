#include <algorithm>
#include <cmath>
#include <cstdio>
#include <map>
#include <vector>
constexpr int MaxN = 2e5 + 5;
class node
{
  public:
    int id;
    int l, r;
    friend bool operator<(const node &, const node &);
};
int b;
int idx;
int n, m;
int p[MaxN];
int cnt[MaxN];
int have[MaxN];
int answer[MaxN];
std::vector<node> v;
std::map<int, int> map;
bool operator<(const node &x, const node &y)
{
    return x.l / b == y.l / b ? x.r == y.r ? false : (x.r < y.r) ^ (x.l / b % 2 == 1) : x.l < y.l;
}
int main()
{
    scanf("%d%d", &n, &m);
    b = n / sqrt(m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &p[i]);
        if (map.find(p[i]) == map.end())
        {
            idx++;
            map[p[i]] = idx;
        }
        p[i] = map[p[i]];
    }
    for (int i = 1; i <= m; i++)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        v.push_back({i, l, r});
    }
    std::sort(v.begin(), v.end());
    int cl, cr;
    cl = 1;
    cr = 0;
    have[0] = n;
    int c = 0;
    for (const auto &[id, l, r] : v)
    {
        for (; l < cl;)
        {
            cl--;
            have[cnt[p[cl]]]--;
            cnt[p[cl]]++;
            have[cnt[p[cl]]]++;
            if (have[c + 1] >= 1)
            {
                c++;
            }
        }
        for (; cr < r;)
        {
            cr++;
            have[cnt[p[cr]]]--;
            cnt[p[cr]]++;
            have[cnt[p[cr]]]++;
            if (have[c + 1] >= 1)
            {
                c++;
            }
        }
        for (; cl < l;)
        {
            have[cnt[p[cl]]]--;
            cnt[p[cl]]--;
            have[cnt[p[cl]]]++;
            cl++;
            if (have[c] == 0)
            {
                c--;
            }
        }
        for (; r < cr;)
        {
            have[cnt[p[cr]]]--;
            cnt[p[cr]]--;
            have[cnt[p[cr]]]++;
            cr--;
            if (have[c] == 0)
            {
                c--;
            }
        }
        answer[id] = c;
    }
    for (int i = 1; i <= m; i++)
    {
        printf("%d\n", -answer[i]);
    }
    return 0;
}