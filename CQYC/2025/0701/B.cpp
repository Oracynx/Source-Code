#include <cstdio>
#include <tuple>
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
};
int n;
int answer;
int p;
int state[MaxN];
table<int, int(5e6 + 7)> map;
int dfs(int x)
{
    if (map.count(x))
    {
        return map[x];
    }
    int result = 1;
    for (int i = 2; i * i <= x; i++)
    {
        if (x % i == 0)
        {
            result += dfs(i);
            if (x / i != i)
            {
                result += dfs(x / i);
            }
        }
    }
    return map[x] = result;
}
int main()
{
    scanf("%d%d", &n, &p);
    for (int i = 2; i <= n; i++)
    {
        answer += 1ll * dfs(i) * i % p;
        answer = answer >= p ? answer - p : answer;
    }
    printf("%d\n", answer);
    return 0;
}