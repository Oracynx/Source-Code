#include <algorithm>
#include <cstdio>
#include <map>
#include <queue>
#include <tuple>
#include <vector>
constexpr int MaxN = 2e5 + 5;
int n, m, k;
int kind[MaxN];
int color[MaxN];
int wanted[MaxN];
int before[MaxN];
bool covered[MaxN];
std::queue<int> queue;
std::vector<std::tuple<int, int>> answer;
std::map<std::tuple<int, int>, int> map;
std::vector<std::tuple<int, int, int>> g[MaxN];
void change(int u, int color, int val)
{
    kind[u] -= map[{u, color}] >= 1 ? 1 : 0;
    map[{u, color}] += val;
    kind[u] += map[{u, color}] >= 1 ? 1 : 0;
}
int query(int u)
{
    return kind[u];
}
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; i++)
    {
        int u, v, x, y;
        scanf("%d%d%d%d", &u, &v, &x, &y);
        g[u].push_back({v, y, i});
        g[v].push_back({u, y, i});
        color[i] = x;
        wanted[i] = y;
        change(u, y, 1);
        change(v, y, 1);
    }
    for (int i = 1; i <= n; i++)
    {
        if (query(i) <= 1)
        {
            queue.push(i);
        }
    }
    for (; !queue.empty();)
    {
        int u = queue.front();
        queue.pop();
        int col = 0;
        for (const auto &[v, y, id] : g[u])
        {
            if (!covered[id])
            {
                col = y;
                before[v] = -1;
            }
        }
        if (col != 0)
        {
            answer.push_back({u, col});
        }
        for (const auto &[v, y, id] : g[u])
        {
            if (!covered[id])
            {
                color[id] = y;
                if (before[v] == -1)
                {
                    before[v] = query(v);
                }
                change(v, y, -1);
            }
        }
        for (const auto &[v, y, id] : g[u])
        {
            if (!covered[id])
            {
                covered[id] = true;
                if (before[v] >= 2 && query(v) <= 1)
                {
                    queue.push(v);
                }
            }
        }
    }
    bool suc = true;
    for (int i = 1; i <= n; i++)
    {
        suc &= color[i] == wanted[i];
    }
    if (!suc)
    {
        printf("-1\n");
        return 0;
    }
    std::reverse(answer.begin(), answer.end());
    printf("%zu\n", answer.size());
    for (const auto &[u, c] : answer)
    {
        printf("%d %d\n", u, c);
    }
    return 0;
}