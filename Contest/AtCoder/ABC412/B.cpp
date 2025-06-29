#include <cstdio>
#include <cstring>
#include <map>
constexpr int MaxN = 1e2 + 5;
int n, m;
char s[MaxN];
char t[MaxN];
std::map<char, bool> map;
int main()
{
    scanf("%s", s + 1);
    scanf("%s", t + 1);
    n = strlen(s + 1);
    m = strlen(t + 1);
    for (int i = 1; i <= m; i++)
    {
        map[t[i]] = true;
    }
    for (int i = 2; i <= n; i++)
    {
        if ('A' <= s[i] && s[i] <= 'Z' && !map[s[i - 1]])
        {
            printf("No\n");
            return 0;
        }
    }
    printf("Yes\n");
    return 0;
}