#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>
constexpr int MaxN = 5e3 + 5;
int n;
int a[MaxN];
int b[MaxN];
std::set<int> set[MaxN];
std::vector<int> answer;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &b[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            set[i].insert(a[i] ^ b[j]);
        }
    }
    for (const auto &val : set[1])
    {
        bool suc = true;
        for (int i = 1; i <= n && suc; i++)
        {
            auto it = set[i].lower_bound(val);
            suc &= it != set[i].end() && *it == val;
        }
        if (suc)
        {
            answer.push_back(val);
        }
    }
    printf("%zu\n", answer.size());
    for (const auto &val : answer)
    {
        printf("%d\n", val);
    }
    return 0;
}
