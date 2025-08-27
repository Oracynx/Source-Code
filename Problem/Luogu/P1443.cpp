#include <cstdio>
#include <queue>
#include <tuple>
#include <vector>
constexpr int MaxN = 4e2 + 5;
int n, m;
int sx, sy;
int p[MaxN][MaxN];
std::queue<std::tuple<int, int, int>> queue;
int main()
{
    scanf("%d%d%d%d", &n, &m, &sx, &sy);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            p[i][j] = -1;
        }
    }
    queue.push({sx, sy, 0});
    for (; !queue.empty();)
    {
        const auto [x, y, d] = queue.front();
        queue.pop();
        if (!(1 <= x && x <= n && 1 <= y && y <= m) || p[x][y] != -1)
        {
            continue;
        }
        p[x][y] = d;
        for (const auto &[dx, dy] : std::vector<std::tuple<int, int>>{
                 {2, 1},
                 {2, -1},
                 {-2, 1},
                 {-2, -1},
                 {1, 2},
                 {1, -2},
                 {-1, 2},
                 {-1, -2},
             })
        {
            queue.push({x + dx, y + dy, d + 1});
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            printf("%d ", p[i][j]);
        }
        printf("\n");
    }
    return 0;
}