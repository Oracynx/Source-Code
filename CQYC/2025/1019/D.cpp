#include <algorithm>
#include <cstdio>
constexpr int MaxN = 3e3 + 5;
int n, m;
int up[MaxN][MaxN];
int down[MaxN][MaxN];
int left[MaxN][MaxN];
int right[MaxN][MaxN];
int gup[MaxN][MaxN];
int gdown[MaxN][MaxN];
int hup[MaxN][MaxN];
int hdown[MaxN][MaxN];
char s[MaxN][MaxN];
bool reverse;
long long answer;
void solve(int sx, int ex, int sy, int ey)
{
    int lx, ly;
    lx = ex - sx + 1;
    ly = ey - sy + 1;
    if (lx <= 1 || ly <= 1)
    {
        return;
    }
    if (lx < ly)
    {
        int mid = (sy + ey) / 2;
        for (int i = sx; i <= ex; i++)
        {
            for (int j = sx; j <= ex; j++)
            {
                gup[i][j] = gdown[i][j] = 0;
                hup[i][j] = hdown[i][j] = 0;
            }
            for (int j = mid; j >= std::max(left[i][mid], sy); j--)
            {
                gup[i][std::max(up[i][j], sx)]++;
                gdown[i][std::min(down[i][j], ex)]++;
            }
            for (int j = mid + 1; j <= std::min(right[i][mid + 1], ey); j++)
            {
                hup[i][std::max(up[i][j], sx)]++;
                hdown[i][std::min(down[i][j], ex)]++;
            }
            for (int j = ex - 1; j >= sx; j--)
            {
                gdown[i][j] += gdown[i][j + 1];
                hdown[i][j] += hdown[i][j + 1];
            }
            for (int j = sx + 1; j <= ex; j++)
            {
                gup[i][j] += gup[i][j - 1];
                hup[i][j] += hup[i][j - 1];
            }
        }
        for (int i = sx; i <= ex; i++)
        {
            for (int j = i + 1; j <= ex; j++)
            {
                if (s[i][mid] != s[j][mid] || s[i][mid] != s[i][mid + 1] || s[i][mid] != s[j][mid + 1])
                {
                    continue;
                }
                int cl, cr;
                cl = cr = 0;
                if (left[i][mid] > left[j][mid])
                {
                    cl = gdown[i][j];
                }
                else
                {
                    cl = gup[j][i];
                }
                if (right[i][mid + 1] < right[j][mid + 1])
                {
                    cr = hdown[i][j];
                }
                else
                {
                    cr = hup[j][i];
                }
                answer += cl * cr;
            }
        }
        solve(sx, ex, sy, mid);
        solve(sx, ex, mid + 1, ey);
    }
    else
    {
        int mid = (sx + ex) / 2;
        for (int i = sy; i <= ey; i++)
        {
            for (int j = sy; j <= ey; j++)
            {
                gup[i][j] = gdown[i][j] = 0;
                hup[i][j] = hdown[i][j] = 0;
            }
            for (int j = mid + 1; j <= std::min(down[mid + 1][i], ex); j++)
            {
                gup[i][std::max(left[j][i], sy)]++;
                gdown[i][std::min(right[j][i], ey)]++;
            }
            for (int j = mid; j >= std::max(up[mid][i], sx); j--)
            {
                hup[i][std::max(left[j][i], sy)]++;
                hdown[i][std::min(right[j][i], ey)]++;
            }
            for (int j = ey - 1; j >= sy; j--)
            {
                gdown[i][j] += gdown[i][j + 1];
                hdown[i][j] += hdown[i][j + 1];
            }
            for (int j = sy + 1; j <= ey; j++)
            {
                gup[i][j] += gup[i][j - 1];
                hup[i][j] += hup[i][j - 1];
            }
        }
        for (int i = sy; i <= ey; i++)
        {
            for (int j = i + 1; j <= ey; j++)
            {
                if (s[mid][i] != s[mid][j] || s[mid][i] != s[mid + 1][i] || s[mid][i] != s[mid + 1][j])
                {
                    continue;
                }
                int cl, cr;
                cl = cr = 0;
                if (down[mid + 1][i] < down[mid + 1][j])
                {
                    cl = gdown[i][j];
                }
                else
                {
                    cl = gup[j][i];
                }
                if (up[mid][i] > up[mid][j])
                {
                    cr = hdown[i][j];
                }
                else
                {
                    cr = hup[j][i];
                }
                answer += cl * cr;
            }
        }
        solve(sx, mid, sy, ey);
        solve(mid + 1, ex, sy, ey);
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", s[i] + 1);
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            up[i][j] = s[i][j] == s[i - 1][j] ? up[i - 1][j] : i;
            left[i][j] = s[i][j] == s[i][j - 1] ? left[i][j - 1] : j;
        }
    }
    for (int i = n; i >= 1; i--)
    {
        for (int j = m; j >= 1; j--)
        {
            down[i][j] = s[i][j] == s[i + 1][j] ? down[i + 1][j] : i;
            right[i][j] = s[i][j] == s[i][j + 1] ? right[i][j + 1] : j;
        }
    }
    solve(1, n, 1, m);
    printf("%lld\n", answer);
    return 0;
}