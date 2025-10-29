#include <algorithm>
#include <cstdio>
#include <map>
#include <set>
const int MaxN = 5e5 + 5;
int n, c;
long long m;
long long answer;
long long p[MaxN];
std::set<long long> set;
std::map<long long, int> map;
long long next(long long u)
{
    auto it = set.upper_bound(u);
    if (it == set.end())
    {
        return -1;
    }
    long long v = *it;
    return v;
}
int main()
{
    scanf("%d%lld%d", &n, &m, &c);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &p[i]);
        map[p[i]]++;
    }
    std::sort(p + 1, p + 1 + n);
    n = std::unique(p + 1, p + 1 + n) - (p + 1);
    for (const auto &[k, v] : map)
    {
        set.insert(k);
        set.insert(k + m);
        set.insert(k + m + m);
    }
    int have = 0;
    long long cur = p[n] + 1;
    for (; have < c;)
    {
        cur = next(cur);
        have += map[cur];
    }
    for (int i = 1; i <= n; i++)
    {
        long long d = i == 1 ? p[1] + m - p[n] : p[i] - p[i - 1];
        answer += d * have;
        have -= map[p[i]];
        for (; have < c;)
        {
            cur = next(cur);
            have += map[cur % m];
        }
    }
    printf("%lld\n", answer);
    return 0;
}