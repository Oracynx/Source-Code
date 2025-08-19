#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
constexpr int MaxN = 2e5 + 5;
int n;
int len[MaxN];
char s[MaxN];
std::vector<int> v[26];
void solve()
{
    scanf("%d", &n);
    scanf("%s", s + 1);
    int count = 1;
    for (int i = 2; i <= n; i++)
    {
        if (s[i - 1] != s[i])
        {
            v[s[i - 1] - 'a'].push_back(count);
            count = 0;
        }
        count++;
    }
    v[s[n] - 'a'].push_back(count);
    for (int i = 0; i < 26; i++)
    {
        len[i] = 0;
        std::sort(v[i].begin(), v[i].end());
    }
    for (int i = 1; i <= n + 1; i++)
    {
        int answer = 0;
        for (int i = 0; i < 26; i++)
        {
            if (!v[i].empty())
            {
                len[i] += v[i].back();
                v[i].pop_back();
            }
            answer = std::max(answer, len[i]);
        }
        printf("%d ", answer);
    }
    printf("\n");
}
int main()
{
    freopen("str.in", "r", stdin);
    freopen("str.out", "w", stdout);
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}