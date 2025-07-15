#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>
constexpr int MaxN = 1e5 + 5;
int n, m;
int in[MaxN];
int cnt[MaxN];
int ref[MaxN];
bool vis[MaxN];
std::vector<int> g[MaxN];
void makeRef(int u, int f, int &index)
{
    ref[u] = ++index;
    for (const auto &v : g[u])
    {
        if (v == f)
        {
            continue;
        }
        makeRef(v, u, index);
    }
}
int main()
{
    freopen("inception.in", "r", stdin);
    freopen("inception.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
        in[u]++;
        in[v]++;
    }
    for (int i = 1; i <= n; i++)
    {
        cnt[in[i]]++;
    }
    if (cnt[1] == 2 && cnt[2] == n - 2)
    {
        int root = -1;
        for (int i = 1; i <= n; i++)
        {
            if (in[i] == 1)
            {
                root = i;
                break;
            }
        }
        int index = 0;
        makeRef(root, 0, index);
        for (int i = 1; i <= m; i++)
        {
            int k;
            scanf("%d", &k);
            std::vector<int> v;
            for (int j = 1; j <= k; j++)
            {
                int x;
                scanf("%d", &x);
                v.push_back(ref[x]);
            }
            std::sort(v.begin(), v.end());
            int answer = std::max(v[0] - 1, n - v.back());
            for (int j = 0; j < int(v.size()) - 1; j++)
            {
                answer = std::max(answer, (v[j + 1] - v[j]) / 2);
            }
            printf("%d\n", answer);
        }
        return 0;
    }
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            vis[j] = false;
        }
        std::queue<int> queue;
        int k;
        scanf("%d", &k);
        for (int j = 1; j <= k; j++)
        {
            int x;
            scanf("%d", &x);
            vis[x] = true;
            queue.push(x);
        }
        for (int i = 0;; i++)
        {
            queue.push(-1);
            for (; !queue.empty();)
            {
                int u = queue.front();
                queue.pop();
                if (u == -1)
                {
                    break;
                }
                for (const auto &v : g[u])
                {
                    if (vis[v])
                    {
                        continue;
                    }
                    queue.push(v);
                    vis[v] = true;
                }
            }
            if (queue.empty())
            {
                printf("%d\n", i);
                break;
            }
        }
    }
    return 0;
}