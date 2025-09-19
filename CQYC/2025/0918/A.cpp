#include <algorithm>
#include <cstdio>
#include <queue>
constexpr int MaxN = 1e3 + 5;
constexpr long long MaxK = 1e6 + 5;
int n, m, k, c;
int p[MaxN][MaxN];
long long answer;
long long al[MaxK];
long long ar[MaxK];
std::priority_queue<long long> queue;
void clear()
{
    for (; !queue.empty();)
    {
        queue.pop();
    }
}
void solve()
{
    scanf("%d%d%d%d", &n, &m, &k, &c);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            scanf("%d", &p[i][j]);
        }
    }
    clear();
    for (int i = 1; i <= n; i++)
    {
        long long x = 0;
        for (int j = 1; j <= m; j++)
        {
            x += p[i][j];
        }
        queue.push(x);
    }
    for (int i = 1; i <= k; i++)
    {
        al[i] = al[i - 1] + queue.top();
        queue.push(queue.top() - c * m);
        queue.pop();
    }
    clear();
    for (int i = 1; i <= m; i++)
    {
        long long x = 0;
        for (int j = 1; j <= n; j++)
        {
            x += p[j][i];
        }
        queue.push(x);
    }
    for (int i = 1; i <= k; i++)
    {
        ar[i] = ar[i - 1] + queue.top();
        queue.push(queue.top() - c * n);
        queue.pop();
    }
    answer = 0;
    for (int i = 0; i <= k; i++)
    {
        answer = std::max(answer, ar[i] + al[k - i] - 1ll * i * (k - i) * c);
        answer = std::max(answer, al[i] + ar[k - i] - 1ll * i * (k - i) * c);
    }
    printf("%lld\n", answer);
}
int main()
{
    int t;
    scanf("%*d%d", &t);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}