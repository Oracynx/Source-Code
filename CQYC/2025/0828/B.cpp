#include <cstdio>
constexpr int MaxN = 2e3 + 5;
int n, m;
int g[26][MaxN][MaxN];
char s[MaxN][MaxN];
long long answer;
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", s[i] + 1);
    }
    bool spA = true;
    for (int j = 1; j <= m; j++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int k = 0; k < 26; k++)
            {
                g[k][i][j] = g[k][i - 1][j];
            }
            g[s[i][j] - 'a'][i][j]++;
            spA &= s[1][1] == s[i][j];
        }
    }
    if (spA)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                answer += (n - i) * (m - j);
            }
        }
        printf("%lld\n", answer);
        return 0;
    }
    if (n * m <= 40000 || (n <= 400 && m <= 400))
    {
        fprintf(stderr, "Bf\n");
        for (int a = 1; a <= n; a++)
        {
            for (int b = a + 1; b <= n; b++)
            {
                int c = 0;
                for (int i = 1; i <= m; i++)
                {
                    if (s[a][i] != s[b][i] || s[a][i] != s[a][i - 1])
                    {
                        if (c >= 2)
                        {
                            answer += c * (c - 1) / 2;
                        }
                        c = 0;
                    }
                    if (s[a][i] == s[b][i])
                    {
                        int d = g[s[a][i] - 'a'][b][i] - g[s[a][i] - 'a'][a - 1][i];
                        if (d == b - a + 1)
                        {
                            c++;
                        }
                    }
                }
                if (c >= 2)
                {
                    answer += c * (c - 1) / 2;
                }
            }
        }
        printf("%lld\n", answer);
        return 0;
    }
    for (int a = 1; a <= n; a++)
    {
        for (int b = a + 1; b <= n; b++)
        {
            int count = 0;
            int c = 0;
            for (int i = 1; i <= m; i++)
            {
                if (s[a][i] != s[b][i] || s[a][i] != s[a][i - 1])
                {
                    if (c >= 2)
                    {
                        answer += c * (c - 1) / 2;
                    }
                    c = 0;
                }
                int d = g[s[a][i] - 'a'][b][i] - g[s[a][i] - 'a'][a - 1][i];
                if (d == b - a + 1)
                {
                    count++;
                    if (s[a][i] == s[b][i])
                    {
                        c++;
                    }
                }
            }
            if (c >= 2)
            {
                answer += c * (c - 1) / 2;
            }
            if (count <= 1)
            {
                break;
            }
        }
    }
    printf("%lld\n", answer);
    return 0;
}