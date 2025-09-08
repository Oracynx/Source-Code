#include <algorithm>
#include <cstdio>
constexpr int MaxN = 1e6 + 5;
constexpr int MaxC = 1e6 + 5;
int n, m, c;
int p[MaxN];
int k[MaxN];
double d;
double px[MaxN];
double dp[2][MaxC];
double answer[MaxC];
int main()
{
    scanf("%d%d%lf", &n, &m, &d);
    d /= 1e5;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }
    int minK, maxK;
    minK = n + 1;
    maxK = 0;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d", &k[i]);
        minK = std::min(minK, k[i]);
        maxK = std::max(maxK, k[i]);
    }
    c = 2;
    auto cp = d;
    for (; cp >= 1e-11;)
    {
        c++;
        cp *= d;
    }
    c = std::min(c, maxK + 2);
    px[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        px[i] = px[i - 1] * d;
    }
    if (minK == n && maxK == n)
    {
        double answer = 0;
        for (int i = 1; i <= n; i++)
        {
            answer += px[i - 1] * p[i];
        }
        for (int i = 1; i <= m; i++)
        {
            printf("%.8lf\n", answer);
        }
        return 0;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= std::min(i, c); j++)
        {
            dp[i & 1][j] = std::max(dp[~i & 1][j], dp[~i & 1][j - 1] + p[i] * px[j - 1]);
        }
    }
    for (int i = 1; i <= c; i++)
    {
        answer[i] = std::max(answer[i - 1], dp[n & 1][i]);
    }
    for (int i = 1; i <= m; i++)
    {
        printf("%.8lf\n", answer[k[i]]);
    }
    return 0;
}
