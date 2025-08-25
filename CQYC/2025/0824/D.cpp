#include <algorithm>
#include <cstdio>
#include <functional>
#include <vector>
constexpr int MaxN = 1e6 + 5;
int n, k;
int p[MaxN];
bool split[MaxN];
std::vector<int> answer[2];
std::vector<std::vector<int>> v;
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }
    int c = 1;
    split[p[1]] = true;
    for (int i = 1; c < k; i++)
    {
        if (split[i])
        {
            continue;
        }
        c++;
        split[i] = true;
    }
    std::vector<int> temp;
    for (int i = 1; i <= n; i++)
    {
        if (split[p[i]])
        {
            if (!temp.empty())
            {
                v.push_back(temp);
                temp.clear();
            }
        }
        temp.push_back(p[i]);
    }
    v.push_back(temp);
    std::sort(v.begin(), v.end(), std::greater<>());
    for (const auto &g : v)
    {
        for (const auto &val : g)
        {
            answer[0].push_back(val);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        split[i] = false;
    }
    c = 1;
    split[p[1]] = true;
    for (int i = n; c < k; i--)
    {
        if (split[i])
        {
            continue;
        }
        c++;
        split[i] = true;
    }
    v.clear();
    temp.clear();
    for (int i = 1; i <= n; i++)
    {
        if (split[p[i]])
        {
            if (!temp.empty())
            {
                v.push_back(temp);
                temp.clear();
            }
        }
        temp.push_back(p[i]);
    }
    v.push_back(temp);
    std::sort(v.begin(), v.end(), std::greater<>());
    for (const auto &g : v)
    {
        for (const auto &val : g)
        {
            answer[1].push_back(val);
        }
    }
    if (answer[0] < answer[1])
    {
        for (const auto &val : answer[0])
        {
            printf("%d ", val);
        }
        printf("\n");
    }
    else
    {
        for (const auto &val : answer[1])
        {
            printf("%d ", val);
        }
        printf("\n");
    }
    return 0;
}