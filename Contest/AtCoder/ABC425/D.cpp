#include <cstdio>
#include <queue>
#include <tuple>
#include <vector>
constexpr int MaxN = 3e5 + 5;
int h, w;
char *s[MaxN];
bool *vis[MaxN];
std::queue<std::tuple<int, int>> queue;
std::vector<std::tuple<int, int>> waiting;
int f(int x, int y)
{
    return (s[x - 1][y] == '#' ? 1 : 0) + (s[x + 1][y] == '#' ? 1 : 0) + (s[x][y - 1] == '#' ? 1 : 0) +
           (s[x][y + 1] == '#' ? 1 : 0);
}
void update()
{
    for (const auto &[x, y] : waiting)
    {
        s[x][y] = '#';
    }
    waiting.clear();
    return;
}
int main()
{
    scanf("%d%d", &h, &w);
    for (int i = 0; i <= h + 5; i++)
    {
        s[i] = new char[w + 5];
        vis[i] = new bool[w + 5];
    }
    for (int i = 1; i <= h; i++)
    {
        scanf("%s", s[i] + 1);
        for (int j = 1; j <= w; j++)
        {
            vis[i][j] = false;
            if (s[i][j] == '#')
            {
                queue.push({i - 1, j});
                queue.push({i + 1, j});
                queue.push({i, j - 1});
                queue.push({i, j + 1});
            }
        }
    }
    queue.push({-1, -1});
    for (; !queue.empty();)
    {
        const auto [x, y] = queue.front();
        queue.pop();
        if (x == -1 && y == -1)
        {
            update();
            if (queue.empty())
            {
                break;
            }
            queue.push({-1, -1});
            continue;
        }
        if (!(1 <= x && x <= h && 1 <= y && y <= w))
        {
            continue;
        }
        if (vis[x][y])
        {
            continue;
        }
        vis[x][y] = true;
        int d = f(x, y);
        if (d == 1)
        {
            waiting.push_back({x, y});
            queue.push({x - 1, y});
            queue.push({x + 1, y});
            queue.push({x, y - 1});
            queue.push({x, y + 1});
        }
    }
    int answer = 0;
    for (int i = 1; i <= h; i++)
    {
        for (int j = 1; j <= w; j++)
        {
            answer += s[i][j] == '#' ? 1 : 0;
        }
    }
    printf("%d\n", answer);
    return 0;
}