#include <cstdio>
#include <functional>
#include <queue>
#include <tuple>
#include <vector>
constexpr int MaxN = 1e6 + 5;
int n, k;
int p[MaxN];
std::priority_queue<std::tuple<int, int>> queueA;
std::priority_queue<std::tuple<int, int>, std::vector<std::tuple<int, int>>, std::greater<>> queueB;
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }
    for (int i = 1; i <= k; i++)
    {
        queueA.push({p[i], i});
        queueB.push({p[i], i});
    }
    printf("%d", std::get<0>(queueB.top()));
    for (int i = k + 1; i <= n; i++)
    {
        queueB.push({p[i], i});
        for (; std::get<1>(queueB.top()) <= i - k;)
        {
            queueB.pop();
        }
        printf(" %d", std::get<0>(queueB.top()));
    }
    printf("\n");
    printf("%d", std::get<0>(queueA.top()));
    for (int i = k + 1; i <= n; i++)
    {
        queueA.push({p[i], i});
        for (; std::get<1>(queueA.top()) <= i - k;)
        {
            queueA.pop();
        }
        printf(" %d", std::get<0>(queueA.top()));
    }
    return 0;
}