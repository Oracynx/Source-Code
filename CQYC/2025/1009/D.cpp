#include <cstdio>
#include <queue>
#include <tuple>
constexpr int MaxN = 3e5 + 5;
int n, k;
int p[MaxN];
int vis[MaxN];
std::queue<std::tuple<int, int>> queue;
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n - 1; i++)
    {
        scanf("%d", &p[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        int answer = 0;
        queue.push({k, i});
        for (; !queue.empty();)
        {
            const auto [d, u] = queue.front();
            queue.pop();
            if (vis[u] == i)
            {
                continue;
            }
            answer++;
            vis[u] = i;
            if (d == 0 || u == n)
            {
                continue;
            }
            queue.push({d - 1, u + 1});
            queue.push({d - 1, p[u]});
        }
        printf("%d ", answer);
    }
    printf("\n");
    return 0;
}