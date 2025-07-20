#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
constexpr int MaxN = 1e7 + 5;
long long answer;
long long l, r, k;
bool vis[MaxN];
bool can[MaxN];
std::vector<int> prime;
int main()
{
    scanf("%lld%lld%lld", &l, &r, &k);
    k = std::min(k, (long long)(std::sqrt(r)));
    for (int i = 2; i <= k; i++)
    {
        if (vis[i])
        {
            continue;
        }
        prime.push_back(i);
        for (int j = 2 * i; j <= k; j += i)
        {
            vis[j] = true;
        }
    }
    for (const auto &val : prime)
    {
        long long begin = l / val * val;
        if (begin < l)
        {
            begin += val;
        }
        if (begin == val)
        {
            begin += val;
        }
        long long end = r / val * val;
        if (end > r)
        {
            end -= val;
        }
        for (long long j = begin; j <= end; j += val)
        {
            can[j - l] = true;
        }
    }
    for (int i = 0; i <= r - l; i++)
    {
        answer ^= can[i] ? 0 : l + i;
    }
    printf("%lld\n", answer);
    return 0;
}