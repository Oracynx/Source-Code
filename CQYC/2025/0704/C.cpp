#include <algorithm>
#include <cstdio>
#include <ctime>
#include <random>
#include <vector>
std::mt19937 rnd(std::random_device{}());
constexpr int MaxN = 2e5 + 5;
constexpr int MaxM = 3e1 + 5;
int n, a, b;
int len[MaxM];
char c[MaxM];
char s[MaxN];
char t[MaxN];
char to[MaxM][MaxM];
std::vector<int> v;
char f(char x)
{
    return c[x - 'a'];
}
bool check(int origin, int count)
{
    int next = (origin - 1ll * a * count % n + n - 1) % n + 1;
    int cp = 1ll * b * count % len[s[origin] - 'a'];
    return to[s[origin] - 'a'][cp] == t[next];
}
double time()
{
    return 1.0 * clock() / CLOCKS_PER_SEC;
}
int main()
{
    freopen("encode.in", "r", stdin);
    freopen("encode.out", "w", stdout);
    scanf("%d%d%d", &n, &a, &b);
    scanf(" %s", c);
    scanf(" %s", s + 1);
    scanf(" %s", t + 1);
    for (int i = 0; i < 26; i++)
    {
        char u = i + 'a';
        for (int j = 0; j < 26; j++)
        {
            to[i][j] = u;
            u = f(u);
            if (i + 'a' == u)
            {
                len[i] = j + 1;
                break;
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        v.push_back(i);
    }
    std::shuffle(v.begin(), v.end(), rnd);
    for (int i = 1;; i++)
    {
        bool suc = true;
        for (int j = 0; j < int(v.size()) && suc; j++)
        {
            if (!check(v[j], i))
            {
                suc = false;
            }
        }
        if (suc)
        {
            printf("%d\n", i);
            break;
        }
        if (time() > 0.985)
        {
            printf("-1\n");
            break;
        }
    }
    return 0;
}