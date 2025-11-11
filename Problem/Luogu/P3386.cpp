#include <algorithm>
#include <cstdio>
#include <queue>
#include <tuple>
#include <vector>
constexpr int MaxN = 2e4 + 5;
int size;
int answer;
int n, m, c;
int lid[MaxN];
int rid[MaxN];
int dist[MaxN];
std::vector<std::tuple<int, int, int>> g[MaxN];
std::vector<std::tuple<int, int, int>>::iterator cur[MaxN];
int node()
{
    return ++size;
}
void add(int u, int v, int w)
{
    g[u].push_back({v, w, g[v].size()});
    g[v].push_back({u, 0, g[u].size() - 1});
}
void bfs(int s)
{
    for (int i = 1; i <= size; i++)
    {
        dist[i] = 0;
        cur[i] = g[i].begin();
    }
    dist[s] = 1;
    std::queue<int> queue;
    queue.push(s);
    for (; !queue.empty();)
    {
        int u = queue.front();
        queue.pop();
        for (const auto &[v, w, r] : g[u])
        {
            if (w == 0)
            {
                continue;
            }
            if (dist[v] != 0)
            {
                continue;
            }
            dist[v] = dist[u] + 1;
            queue.push(v);
        }
    }
}
int push(int u, int flow, int t)
{
    if (u == t || flow == 0)
    {
        return flow;
    }
    for (auto &it = cur[u]; it != g[u].end(); it++)
    {
        auto &[v, w, r] = *it;
        auto &[rv, rw, rr] = g[v][r];
        if (w > 0 && dist[u] + 1 == dist[v])
        {
            int nflow = push(v, std::min(w, flow), t);
            if (nflow > 0)
            {
                w -= nflow;
                rw += nflow;
                return nflow;
            }
        }
    }
    return 0;
}
int main()
{
    scanf("%d%d%d", &n, &m, &c);
    int s = node();
    int t = node();
    for (int i = 1; i <= n; i++)
    {
        lid[i] = node();
        add(s, lid[i], 1);
    }
    for (int i = 1; i <= m; i++)
    {
        rid[i] = node();
        add(rid[i], t, 1);
    }
    for (int i = 1; i <= c; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add(lid[u], rid[v], 1);
    }
    for (;;)
    {
        bfs(s);
        int flow = push(s, 0x3f3f3f3f, t);
        answer += flow;
        if (flow == 0)
        {
            break;
        }
    }
    printf("%d\n", answer);
    return 0;
}