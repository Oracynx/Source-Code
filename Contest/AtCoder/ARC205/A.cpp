#include <cstdio>
constexpr int MaxN = 5e2 + 5;
int n, m;
int p[MaxN][MaxN];
char s[MaxN][MaxN];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", s[i] + 1);
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            p[i][j] = p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1] +
                      (s[i][j] == '.' && s[i + 1][j] == '.' && s[i][j + 1] == '.' && s[i + 1][j + 1] == '.' ? 1 : 0);
        }
    }
    for (int i = 1; i <= m; i++)
    {
        int sx, ex, sy, ey;
        scanf("%d%d%d%d", &sx, &ex, &sy, &ey);
        printf("%d\n", p[ex - 1][ey - 1] - p[sx - 1][ey - 1] - p[ex - 1][sy - 1] + p[sx - 1][sy - 1]);
    }
    return 0;
}