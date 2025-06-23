#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
constexpr int MaxN = 1e6 + 5;
constexpr int CharSet = 62;
constexpr long long Mod = 998'244'353;
int n;
int sumCount[CharSet][MaxN];
char s[MaxN];
long long answer;
long long aftPow[MaxN];
std::vector<int> v[CharSet];
int cc(char c)
{
    return '0' <= c && c <= '9' ? c - '0' : 'a' <= c && c <= 'z' ? 10 + (c - 'a') : 36 + (c - 'A');
}
int query(int l, int r, int c)
{
    return sumCount[c][r] - sumCount[c][l - 1];
}
long long diff(int l, long long da, long long db)
{
    long long can = (n - l + 1) - da - db;
    long long result = can * (can - 1) / 2;
    result -= aftPow[l] - da * (da - 1) / 2 - db * (db - 1) / 2;
    return result % Mod;
}
void solve()
{
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = 0; i < CharSet; i++)
    {
        v[i].clear();
    }
    for (int i = 1; i <= n; i++)
    {
        v[cc(s[i])].push_back(i);
        for (int j = 0; j < CharSet; j++)
        {
            sumCount[j][i] = sumCount[j][i - 1];
        }
        sumCount[cc(s[i])][i]++;
    }
    for (int i = 1; i <= n; i++)
    {
        aftPow[i] = 0;
        for (int j = 0; j < CharSet; j++)
        {
            long long x = query(i, n, j);
            aftPow[i] += x * (x - 1) / 2;
            aftPow[i] %= Mod;
        }
    }
    answer = 0;
    for (int a = 0; a < CharSet; a++)
    {
        for (int b = 0; b < CharSet; b++)
        {
            int last = 0;
            long long da = 0;
            long long db = 0;
            long long pre = 0;
            long long lSum = 0;
            if (a == b)
            {
                continue;
            }
            for (const auto &i : v[b])
            {
                db++;
                if (last == 0)
                {
                    da = lSum += query(1, i - 1, a);
                    lSum %= Mod;
                    last = i;
                    continue;
                }
                int temp = query(last + 1, i - 1, a);
                pre += lSum * temp;
                da += temp;
                pre %= Mod;
                last = i;
                answer += pre * diff(i + 1, sumCount[a][n] - da, sumCount[b][n] - db) % Mod;
                answer %= Mod;
                lSum += da;
                lSum %= Mod;
            }
        }
    }
    printf("%lld\n", answer);
}
int main()
{
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}
