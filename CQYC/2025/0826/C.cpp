#include <cmath>
#include <cstdio>
#include <vector>
constexpr int MaxN = 1e7 + 5;
int n;
char s[MaxN];
char t[MaxN];
long long answer;
void solve()
{
    scanf("%d", &n);
    scanf(" %s", s + 1);
    scanf(" %s", t + 1);
    if (s[1] != t[1] || s[n] != t[n])
    {
        printf("-1\n");
        return;
    }
    for (int i = 1; i <= n - 1; i++)
    {
        s[i] = s[i] != s[i + 1] ? '1' : '0';
        t[i] = t[i] != t[i + 1] ? '1' : '0';
    }
    for (int i = 2; i <= n - 1; i += 2)
    {
        s[i] = s[i] == '1' ? '0' : '1';
        t[i] = t[i] == '1' ? '0' : '1';
    }
    std::vector<int> vs;
    std::vector<int> vt;
    for (int i = 1; i <= n - 1; i++)
    {
        if (s[i] == '1')
        {
            vs.push_back(i);
        }
        if (t[i] == '1')
        {
            vt.push_back(i);
        }
    }
    if (vs.size() != vt.size())
    {
        printf("-1\n");
        return;
    }
    answer = 0;
    for (int i = 0; i < int(vs.size()); i++)
    {
        answer += abs(vs[i] - vt[i]);
    }
    printf("%lld\n", answer);
}
int main()
{
    int t;
    scanf("%*d%d", &t);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}