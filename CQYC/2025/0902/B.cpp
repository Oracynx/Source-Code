#include <algorithm>
#include <cstdio>
#include <set>
#include <tuple>
constexpr int MaxN = 1e5 + 5;
int n, m;
int d[MaxN];
int v[MaxN];
int p[MaxN];
int t[MaxN];
int w[MaxN];
int next[MaxN];
bool kill[MaxN];
bool live[MaxN];
double when[MaxN];
void build()
{
    std::set<std::tuple<double, int, int>> event;
    std::set<int> set;
    for (int i = 1; i <= n; i++)
    {
        if (kill[i])
        {
            continue;
        }
        next[i] = -1;
        live[i] = true;
        set.insert(i);
    }
    if (set.empty())
    {
        return;
    }
    auto it = set.begin();
    auto pre = it++;
    for (; it != set.end(); it++, pre++)
    {
        const auto &x = *pre;
        const auto &y = *it;
        if (v[x] <= v[y])
        {
            continue;
        }
        int dv = v[x] - v[y];
        event.insert({1.0 * (w[y] - w[x]) / dv, x, y});
    }
    for (; !event.empty();)
    {
        const auto [time, x, y] = *event.begin();
        event.erase(event.begin());
        if (!live[x] || !live[y])
        {
            continue;
        }
        next[x] = y;
        when[x] = time;
        // printf("On time %.2lf, %d catch %d.\n", time, x, y);
        auto it = set.lower_bound(x);
        if (it == set.begin())
        {
            continue;
        }
        it--;
        const auto nx = *it;
        it++;
        it++;
        if (it == set.end())
        {
            continue;
        }
        const auto ny = *it;
        it--;
        live[x] = false;
        set.erase(it);
        if (v[nx] <= v[ny])
        {
            continue;
        }
        int dv = v[nx] - v[ny];
        event.insert({1.0 * (w[ny] - w[nx]) / dv, nx, ny});
    }
}
long long solve(int u, int t)
{
    for (;;)
    {
        if (next[u] == -1 || when[u] > t)
        {
            break;
        }
        u = next[u];
    }
    return w[u] + 1ll * t * v[u];
}
int main()
{
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
    {
        scanf("%d", &d[i]);
        w[i] = w[i - 1] + d[i];
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &v[i]);
    }
    int changed = n + 1;
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &p[i], &t[i]);
        if (p[i] == 0)
        {
            if (!kill[t[i]])
            {
                changed = std::max(changed, t[i]);
            }
            kill[t[i]] = true;
            continue;
        }
        if (kill[p[i]])
        {
            continue;
        }
        if (p[i] <= changed)
        {
            build();
            changed = n + 1;
        }
        printf("%lld\n", solve(p[i], t[i]));
    }
    return 0;
}