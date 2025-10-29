#include <cstdio>
#include <cstdlib>
constexpr int MaxN = 1e5 + 5;
int n, m;
int p[MaxN];
long long answer;
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
        answer += i == 1 ? 0 : abs(p[i] - p[i - 1]);
    }
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &p[i]);
        answer += i == 1 ? 0 : abs(p[i] - p[i - 1]);
    }
    printf("%lld\n", answer);
    return 0;
}