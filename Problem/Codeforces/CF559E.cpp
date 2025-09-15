#include <algorithm>
#include <cstdio>
#include <tuple>
#include <vector>
constexpr int MaxN = 1e2 + 5;
int n;
int s[MaxN];
int x[MaxN];
int dp[MaxN][MaxN][2];
std::vector<std::tuple<int, int>> v;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &s[i], &x[i]);
        v.push_back({s[i], x[i]});
    }
    std::sort(v.begin(), v.end());
    for (int i = 1; i <= n; i++)
    {
        s[i] = std::get<0>(v[i - 1]);
        x[i] = std::get<1>(v[i - 1]);
    }
    s[0] = -1e9;
    x[0] = 0;
    int answer = 0;
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            for (int c = 0; c < 2; c++)
            {
                answer = std::max(answer, dp[i][j][c]);
                int end = s[j] + x[j] * c;
                int right = -1e9;
                int a, b;
                for (int k = i + 1; k <= n; k++)
                {
                    for (int d = 0; d < 2; d++)
                    {
                        int t = s[k] + x[k] * d;
                        if (t > right)
                        {
                            right = t;
                            a = k;
                            b = d;
                        }
                        dp[k][a][b] = std::max(dp[k][a][b], dp[i][j][c] + std::min(x[k], t - end) + right - t);
                    }
                }
            }
        }
    }
    printf("%d\n", answer);
    return 0;
}