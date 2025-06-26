#include <algorithm>
#include <cstdio>
#include <tuple>
#include <utility>
#include <vector>
template <typename tp, int tableSize> class table
{
  public:
    std::vector<std::vector<std::tuple<tp, int>>> data;
    unsigned long long splitMix64(unsigned long long x) const
    {
        x += 0x9e3779b97f4a7c15ull;
        x ^= x >> 30;
        x *= 0xbf58476d1ce4e5b9ull;
        x ^= x >> 27;
        x *= 0x94d049bb133111ebull;
        x ^= x >> 31;
        return x;
    }
    table()
    {
        data.resize(tableSize);
    }
    int &operator[](int key)
    {
        auto id = splitMix64(key) % tableSize;
        for (int i = 0; i < int(data[id].size()); i++)
        {
            if (std::get<0>(data[id][i]) == key)
            {
                return std::get<1>(data[id][i]);
            }
        }
        data[id].push_back({key, 0});
        return std::get<1>(data[id][int(data[id].size()) - 1]);
    }
    bool count(int key)
    {
        auto id = splitMix64(key) % tableSize;
        for (int i = 0; i < int(data[id].size()); i++)
        {
            if (std::get<0>(data[id][i]) == key)
            {
                return true;
            }
        }
        return false;
    }
    int &operator[](std::tuple<int, int> key)
    {
        auto id = (splitMix64(std::get<0>(key)) ^ splitMix64(std::get<1>(key))) % tableSize;
        for (int i = 0; i < int(data[id].size()); i++)
        {
            if (std::get<0>(data[id][i]) == key)
            {
                return std::get<1>(data[id][i]);
            }
        }
        data[id].push_back({key, 0});
        return std::get<1>(data[id][int(data[id].size()) - 1]);
    }
    bool count(std::tuple<int, int> key)
    {
        auto id = (splitMix64(std::get<0>(key)) ^ splitMix64(std::get<1>(key))) % tableSize;
        for (int i = 0; i < int(data[id].size()); i++)
        {
            if (std::get<0>(data[id][i]) == key)
            {
                return true;
            }
        }
        return false;
    }
};
table<int, int(5e6 + 7)> sap;
table<std::tuple<int, int>, int(5e6 + 7)> map;
int split(int x)
{
    if (sap.count(x))
    {
        return sap[x];
    }
    int cp = x;
    int count = 0;
    for (int i = 2; i * i <= cp; i++)
    {
        for (; x % i == 0;)
        {
            x /= i;
            count++;
        }
    }
    return sap[cp] = count + 1;
}
int calc(int a, int b)
{
    if (a > b)
    {
        std::swap(a, b);
    }
    if (a == 1)
    {
        return 0;
    }
    if (a == b)
    {
        return 1;
    }
    if (map.count({a, b}))
    {
        return map[{a, b}];
    }
    int c = b - a;
    int result = a - 1;
    for (int i = 1; i * i <= c; i++)
    {
        if (c % i != 0)
        {
            continue;
        }
        int x = i;
        if (x != 1)
        {
            if (a >= x)
            {
                int d = a - a / x * x;
                if (d + split(x) <= result)
                {
                    result = std::min(result, d + split(x) + calc(a / x, b / x));
                }
            }
            {
                int d = (a / x + 1) * x - a;
                if (d + split(x) <= result)
                {
                    result = std::min(result, d + split(x) + calc(a / x + 1, b / x + 1));
                }
            }
        }
        x = c / i;
        if (x != 1)
        {
            if (a >= x)
            {
                int d = a - a / x * x;
                if (d + split(x) <= result)
                {
                    result = std::min(result, d + split(x) + calc(a / x, b / x));
                }
            }
            {
                int d = (a / x + 1) * x - a;
                if (d + split(x) <= result)
                {
                    result = std::min(result, d + split(x) + calc(a / x + 1, b / x + 1));
                }
            }
        }
    }
    return map[{a, b}] = result;
}
void solve()
{
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%d\n", calc(a, b));
}
int main()
{
    freopen("energy.in", "r", stdin);
    freopen("energy.out", "w", stdout);
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}
