#include <cstdio>
constexpr int MaxN = 3e1 + 5;
constexpr int MaxM = 5e4 + 5;
int n, m;
int cl, cr;
int sum[MaxN][MaxM];
char s[MaxN][MaxM];
long long answer;
int query(int sx, int ex, int sy, int ey)
{
    return sum[ex][ey] - sum[sx - 1][ey] - sum[ex][sy - 1] + sum[sx - 1][sy - 1];
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf(" %s", s[i] + 1);
        for (int j = 1; j <= m; j++)
        {
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + (s[i][j] == '1' ? 1 : 0);
        }
    }
    scanf("%d%d", &cl, &cr);
    for (int sx = 1; sx <= n; sx++)
    {
        for (int ex = sx; ex <= n; ex++)
        {
            int sy, ey;
            sy = 0;
            ey = 0;
            int cs, ce;
            cs = 0;
            ce = 0;
            for (int i = 1; i <= m; i++)
            {
                if (i >= 2)
                {
                    int delta = query(sx, ex, i - 1, i - 1);
                    cs -= delta;
                    ce -= delta;
                }
                for (; cs < cl || sy < i;)
                {
                    sy++;
                    if (sy > m)
                    {
                        sy = -1;
                        break;
                    }
                    cs += query(sx, ex, sy, sy);
                }
                for (; ce <= cr && ey + 1 <= m;)
                {
                    ey++;
                    int delta = query(sx, ex, ey, ey);
                    if (ce + delta > cr)
                    {
                        ey--;
                        break;
                    }
                    else
                    {
                        ce += delta;
                    }
                }
                if (sy == -1)
                {
                    break;
                }
                answer += ey - sy + 1;
            }
        }
    }
    printf("%lld\n", answer);
    return 0;
}
