#include <algorithm>
#include <cstdio>
constexpr int MaxN = 1e3 + 5;
int n, m;
int p[MaxN];
int s[MaxN];
double answer;
void check()
{
    double temp = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (s[j] >= p[i])
            {
                temp += 1.0 / n;
            }
        }
    }
    answer = std::max(answer, temp);
}
void dfs(int u, int st, int mx)
{
    if (u >= n + 1)
    {
        check();
        return;
    }
    if (u == n)
    {
        s[u] = st;
        dfs(u + 1, 0, mx);
    }
    for (int i = s[u - 1]; i <= std::min(st, mx); i++)
    {
        s[u] = i;
        dfs(u + 1, st - i, mx);
    }
}
int main()
{
    freopen("crazy.in", "r", stdin);
    freopen("crazy.out", "w", stdout);
    scanf("%d%d", &n, &m);
    int maxV = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
        maxV = std::max(maxV, p[i]);
    }
    dfs(1, m, maxV);
    printf("%.12lf\n", n - answer);
    return 0;
}