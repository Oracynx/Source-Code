#include <cstdio>
constexpr int MaxN = 2e6 + 5;
constexpr long long Mod = 998'244'353;
int n;
int cnt[26];
char s[MaxN];
long long answer;
long long ca[MaxN];
long long cb[MaxN];
long long pe[MaxN];
long long se[MaxN];
long long pw[MaxN];
int main()
{
    scanf("%d", &n);
    pw[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        pw[i] = pw[i - 1] * 2 % Mod;
    }
    scanf("%s", s + 1);
    for (int i = 1; i <= n; i++)
    {
        cnt[s[i] - 'a']++;
    }
    for (int i = 0; i < 26; i++)
    {
        if (cnt[i] == 0)
        {
            ca[i] = 0;
            cb[i] = 1;
        }
        else
        {
            ca[i] = pw[cnt[i] - 1];
            cb[i] = pw[cnt[i] - 1];
        }
    }
    pe[0] = cb[0];
    se[25] = cb[25];
    for (int i = 1; i < 26; i++)
    {
        pe[i] = pe[i - 1] * cb[i] % Mod;
    }
    for (int i = 24; i >= 0; i--)
    {
        se[i] = se[i + 1] * cb[i] % Mod;
    }
    answer += pe[25] - 1;
    answer %= Mod;
    for (int j = 0; j < 26; j++)
    {
        answer += (j == 0 ? 1 : pe[j - 1]) * ca[j] % Mod * (j == 25 ? 1 : se[j + 1]);
        answer %= Mod;
    }
    printf("%lld\n", answer);
    return 0;
}