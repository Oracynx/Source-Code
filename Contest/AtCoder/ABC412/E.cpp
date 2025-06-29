#include <algorithm>
#include <cstdio>
#include <tuple>
#include <vector>
template <int tableSize> class table
{
  public:
    std::vector<std::vector<std::tuple<unsigned long long, bool>>> data;
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
    bool &operator[](unsigned long long key)
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
    bool count(unsigned long long key)
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
constexpr int MaxN = 1e7 + 5;
int answer;
long long len;
long long l, r;
bool vis[MaxN];
bool visBig[MaxN];
std::vector<long long> prime;
table<int(5e6 + 7)> map;
void init(long long limit)
{
    for (long long i = 2; i <= limit; i++)
    {
        if (vis[i])
        {
            continue;
        }
        prime.push_back(i);
        for (int j = 2 * i; j <= limit; j += i)
        {
            vis[j] = true;
        }
    }
}
int main()
{
    init(1e7);
    scanf("%lld%lld", &l, &r);
    len = r - l + 1;
    for (const auto &val : prime)
    {
        for (long long j = std::max(2ll, l / val + (l % val != 0 ? 1 : 0)); j <= r / val; j++)
        {
            long long x = val * j;
            visBig[x - l] = true;
        }
    }
    for (long long i = 1; i <= len - 1; i++)
    {
        if (!visBig[i])
        {
            map[l + i] = true;
        }
    }
    for (const auto &val : prime)
    {
        __int128 x = val;
        for (; x <= r;)
        {
            if (l < x)
            {
                map[x] = true;
            }
            x *= val;
        }
    }
    for (long long i = l; i <= r; i++)
    {
        answer += map[i] ? 1 : 0;
    }
    printf("%d\n", answer + 1);
    return 0;
}