#include <algorithm>
#include <cstdio>
#include <cstring>
constexpr int MaxN = 1e5 + 5;
int n, m, k;
int next[26][MaxN];
int last[26][MaxN];
char s[MaxN];
char t[MaxN];
int main()
{
    scanf("%s", s + 1);
    scanf("%s", t + 1);
    n = strlen(s + 1);
    m = strlen(t + 1);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            last[j][i] = last[j][i - 1];
        }
        last[s[i] - 'a'][i] = i;
    }
    for (int i = n; i >= 1; i--)
    {
        for (int j = 0; j < 26; j++)
        {
            next[j][i] = next[j][i + 1];
        }
        next[s[i] - 'a'][i] = i;
    }
    scanf("%d", &k);
    for (int i = 1; i <= k; i++)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        if (m == 1)
        {
            printf("%d\n", next[t[1] - 'a'][l] <= r ? r - l : r - l + 1);
        }
        else if (m == 2)
        {
            int a, b;
            a = next[t[1] - 'a'][l];
            b = last[t[2] - 'a'][r];
            if (l <= a && a < b && b <= r)
            {
                printf("%d\n", (r - l + 1) - 2);
            }
            else
            {
                int ca, cb, cc;
                ca = 0x3f3f3f3f;
                cb = 0x3f3f3f3f;
                if (l <= a && a <= r)
                {
                    ca = a <= r - 1 ? (r - l + 1) - 1 : (r - l + 1);
                }
                if (l <= b && b <= r)
                {
                    cb = l + 1 <= b ? (r - l + 1) - 1 : (r - l + 1);
                }
                if (r - l + 1 >= 2)
                {
                    cc = r - l + 1;
                }
                else
                {
                    cc = 2;
                }
                printf("%d\n", std::min({ca, cb, cc}));
            }
        }
    }
    return 0;
}