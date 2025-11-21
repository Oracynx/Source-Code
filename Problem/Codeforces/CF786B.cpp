#include <algorithm>
#include <cstdio>
#include <functional>
#include <queue>
#include <tuple>
#include <vector>
constexpr int MaxN = 1e6 + 5;
class node
{
  public:
    static int index;
    int id;
    node *left;
    node *right;
    node()
    {
        id = ++index;
        left = nullptr;
        right = nullptr;
    }
};
int node::index = 0;
int n, m, c, s;
int ref[2][MaxN];
bool vis[MaxN];
long long dis[MaxN];
node *rootUp;
node *rootDown;
std::vector<std::tuple<int, int>> g[MaxN];
void add(int u, int v, int w)
{
    g[u].push_back({v, w});
}
void buildUp(node *c, int s, int t)
{
    if (s == t)
    {
        ref[0][s] = c->id;
        return;
    }
    int mid = (s + t) / 2;
    c->left = new node;
    c->right = new node;
    add(c->left->id, c->id, 0);
    add(c->right->id, c->id, 0);
    buildUp(c->left, s, mid);
    buildUp(c->right, mid + 1, t);
}
void buildDown(node *c, int s, int t)
{
    if (s == t)
    {
        ref[1][s] = c->id;
        return;
    }
    printf("Build in [%d, %d]\n", s, t);
    int mid = (s + t) / 2;
    c->left = new node;
    c->right = new node;
    add(c->id, c->left->id, 0);
    add(c->id, c->right->id, 0);
    buildDown(c->left, s, mid);
    buildDown(c->right, mid + 1, t);
}
void addTo(node *c, int s, int t, int l, int r, int u, int w)
{
    if (l <= s && t <= r)
    {
        add(u, c->id, w);
        return;
    }
    int mid = (s + t) / 2;
    if (l <= mid)
    {
        addTo(c->left, s, mid, l, r, u, w);
    }
    if (r > mid)
    {
        addTo(c->right, mid + 1, t, l, r, u, w);
    }
}
void addFrom(node *c, int s, int t, int l, int r, int u, int w)
{
    if (l <= s && t <= r)
    {
        add(c->id, u, w);
        return;
    }
    int mid = (s + t) / 2;
    if (l <= mid)
    {
        addFrom(c->left, s, mid, l, r, u, w);
    }
    if (r > mid)
    {
        addFrom(c->right, mid + 1, t, l, r, u, w);
    }
}
int main()
{
    scanf("%d%d%d", &n, &m, &s);
    rootUp = new node;
    buildUp(rootUp, 1, n);
    rootDown = new node;
    buildDown(rootDown, 1, n);
    for (int i = 1; i <= n; i++)
    {
        add(ref[1][i], ref[0][i], 0);
    }
    for (int i = 1; i <= m; i++)
    {
        int op;
        scanf("%d", &op);
        if (op == 1)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            add(ref[0][u], ref[1][v], w);
        }
        else if (op == 2)
        {
            int u, l, r, w;
            scanf("%d%d%d%d", &u, &l, &r, &w);
            addTo(rootDown, 1, n, l, r, ref[0][u], w);
        }
        else if (op == 3)
        {
            int u, l, r, w;
            scanf("%d%d%d%d", &u, &l, &r, &w);
            addFrom(rootUp, 1, n, l, r, ref[1][u], w);
        }
    }
    c = node::index;
    std::fill(dis + 1, dis + 1 + c, 0x3f3f3f3f'3f3f3f3f);
    dis[ref[1][s]] = 0;
    std::priority_queue<std::tuple<long long, int>, std::vector<std::tuple<long long, int>>, std::greater<>> queue;
    queue.push({0, ref[1][s]});
    for (; !queue.empty();)
    {
        const auto [d, u] = queue.top();
        queue.pop();
        if (vis[u])
        {
            continue;
        }
        vis[u] = true;
        for (const auto &[v, w] : g[u])
        {
            if (dis[u] + w < dis[v])
            {
                dis[v] = dis[u] + w;
                queue.push({dis[v], v});
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        int u = ref[0][i];
        printf("%lld ", dis[u] == 0x3f3f3f3f'3f3f3f3f ? -1 : dis[u]);
    }
    return 0;
}