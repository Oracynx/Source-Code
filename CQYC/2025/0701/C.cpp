// 可恶的安慕希玩家

#include <algorithm>
#include <cstdio>
#include <vector>
class item
{
  public:
    long long v, l, t;
    item()
    {
        v = 0;
        l = 0;
        t = 0;
    }
    item(const int &_v, const int &_l, const int &_t)
    {
        v = _v;
        l = _l;
        t = _t;
    }
    friend item operator+(const item &a, const item &b)
    {
        long long x = std::max(a.l, b.l);
        item c;
        c.v = a.v + b.v;
        c.l = x + 1;
        c.t = a.t * (1 << (x - a.l)) + b.t * (1 << (x - b.l)) + (1 << x);
        return c;
    }
    friend bool operator<(const item &a, const item &b)
    {
        return a.l < b.l;
    }
};
int n;
long long answer;
std::vector<item> v;
std::vector<item> temp[2];
int main()
{
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    scanf("%d", &n);
    v.push_back({0, 0, 0});
    for (int i = 1; i <= n; i++)
    {
        int x;
        scanf("%d", &x);
        v.push_back({x, 0, 0});
    }
    int now = 0;
    for (; v.size() != 1;)
    {
        std::sort(v.begin(), v.end());
        temp[0].clear();
        temp[1].clear();
        for (const auto &val : v)
        {
            temp[val.l == now].push_back(val);
        }
        v.clear();
        for (int i = 0; i + 1 < int(temp[0].size()); i += 2)
        {
            v.push_back(temp[0][i] + temp[0][i + 1]);
            answer += v.back().v;
        }
        if (int(temp[0].size()) % 2 == 1)
        {
            v.push_back(temp[0].back());
        }
        for (int i = 0; i + 1 < int(temp[1].size()); i += 2)
        {
            v.push_back(temp[1][i] + temp[1][i + 1]);
            answer += v.back().v;
        }
        if (int(temp[1].size()) % 2 == 1)
        {
            v.push_back(temp[1].back());
        }
        now++;
    }
    answer += v[0].t;
    printf("%lld\n", answer);
    return 0;
}