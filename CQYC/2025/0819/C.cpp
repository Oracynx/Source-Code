#include <cstdio>
#include <cstdlib>
constexpr int MaxN = 1e3 + 5;
constexpr int MaxK = 3e5 + 5;
int n, m, k;
int sx[MaxK];
int sy[MaxK];
int ex[MaxK];
int ey[MaxK];
int cover[26][MaxN][MaxN];
int deltaCover[26][MaxN][MaxN];
char c[MaxK];
char s[MaxN][MaxN];
long long temp[26];
long long delta[26][MaxN][MaxN];
int main()
{
    freopen("paint.in", "r", stdin);
    freopen("paint.out", "w", stdout);
    scanf("%d%d%d%*d", &n, &m, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", s[i] + 1);
        for (int j = 1; j <= m; j++)
        {
            cover[s[i][j] - 'a'][i][j] += k;
        }
    }
    for (int i = 1; i <= k; i++)
    {
        scanf("%d%d%d%d", &sx[i], &sy[i], &ex[i], &ey[i]);
        scanf(" %c", &c[i]);
        deltaCover[c[i] - 'a'][sx[i]][sy[i]]++;
        deltaCover[c[i] - 'a'][sx[i]][ey[i] + 1]--;
        deltaCover[c[i] - 'a'][ex[i] + 1][sy[i]]--;
        deltaCover[c[i] - 'a'][ex[i] + 1][ey[i] + 1]++;
    }
    for (int c = 0; c < 26; c++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                deltaCover[c][i][j] = deltaCover[c][i - 1][j] + deltaCover[c][i][j - 1] - deltaCover[c][i - 1][j - 1] +
                                      deltaCover[c][i][j];
                cover[s[i][j] - 'a'][i][j] -= deltaCover[c][i][j];
                cover[c][i][j] += deltaCover[c][i][j];
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            for (int c = 0; c < 26; c++)
            {
                temp[c] = 0;
            }
            int left, right;
            left = 0;
            right = 0;
            for (int c = 0; c < 26; c++)
            {
                temp[0] += cover[c][i][j] * c;
                right += cover[c][i][j];
            }
            left += cover[0][i][j];
            right -= cover[0][i][j];
            for (int c = 1; c < 26; c++)
            {
                temp[c] = temp[c - 1] + left - right;
                left += cover[c][i][j];
                right -= cover[c][i][j];
            }
            int origin = s[i][j] - 'a';
            for (int c = 0; c < 26; c++)
            {
                delta[c][i][j] =
                    delta[c][i - 1][j] + delta[c][i][j - 1] - delta[c][i - 1][j - 1] + (temp[c] - temp[origin]);
            }
        }
    }
    long long base = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            for (int c = 0; c < 26; c++)
            {
                base += abs((s[i][j] - 'a') - c) * deltaCover[c][i][j];
            }
        }
    }
    int w = -1;
    long long answer = 0x3f3f3f3f'3f3f3f3f;
    for (int i = 1; i <= k; i++)
    {
        long long d = base + (delta[c[i] - 'a'][ex[i]][ey[i]] - delta[c[i] - 'a'][sx[i] - 1][ey[i]] -
                              delta[c[i] - 'a'][ex[i]][sy[i] - 1] + delta[c[i] - 'a'][sx[i] - 1][sy[i] - 1]);
        if (d < answer)
        {
            w = i;
            answer = d;
        }
    }
    printf("%lld %d\n", answer, w);
    return 0;
}