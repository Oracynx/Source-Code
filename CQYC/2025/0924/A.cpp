#include <algorithm>
#include <cstdio>
#include <functional>
#include <tuple>
#include <vector>
constexpr int MaxN = 1e6 + 5;
int n, m;
int a, b;
char op[MaxN];
bool skip[MaxN];
long long answer;
long long p[MaxN];
int main()
{
    scanf("%d%d%d%d", &n, &m, &a, &b);
    int c = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf(" %c%lld", &op[i], &p[i]);
        if (op[i] == 'B' && p[i] == 1)
        {
            i--;
            n--;
            continue;
        }
        if (op[i] == 'B')
        {
            c++;
        }
    }
    std::vector<int> ch;
    for (int i = 0; i <= c; i++)
    {
        if (i * b > m)
        {
            break;
        }
        std::vector<std::tuple<long long, int>> v;
        if (i >= 1)
        {
            long long ad = 1;
            long long af = 0;
            for (int i = n; i >= 1; i--)
            {
                if (skip[i])
                {
                    continue;
                }
                if (op[i] == 'A')
                {
                    af += p[i] * ad;
                }
                else if (op[i] == 'B')
                {
                    ad *= p[i];
                    v.push_back({af * (p[i] - 1), i});
                }
            }
            std::sort(v.begin(), v.end(), std::greater<>());
            int u = std::get<1>(v[0]);
            skip[u] = true;
            ch.push_back(p[u]);
            v.clear();
        }
        long long ad = 1;
        long long af = 0;
        for (int i = 1; i <= n; i++)
        {
            if (skip[i])
            {
                continue;
            }
            if (op[i] == 'B')
            {
                af += p[i] * ad;
            }
            else
            {
                ad *= p[i];
                v.push_back({af * p[i], i});
            }
        }
        std::sort(v.begin(), v.end(), std::greater<>());
        int r = std::min(int(v.size()), (m - i * b) / a);
        long long x = 1;
        for (int i = 0; i < r; i++)
        {
            int u = std::get<1>(v[i]);
            skip[u] = true;
            x += p[u];
        }
        for (int i = 1; i <= n; i++)
        {
            if (skip[i])
            {
                continue;
            }
            x = op[i] == 'A' ? x + p[i] : x * p[i];
        }
        for (const auto &val : ch)
        {
            x *= val;
        }
        answer = std::max(answer, x);
        for (int j = 1; j <= n; j++)
        {
            if (op[j] == 'A')
            {
                skip[j] = false;
            }
        }
        // printf("%lld\n", x);
    }
    printf("%lld\n", answer);
    return 0;
}