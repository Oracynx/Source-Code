#include <cstdio>
#include <cstdlib>
#include <map>
constexpr int MaxN = 2e5 + 5;
int n;
int x[MaxN];
int y[MaxN];
std::map<int, int> map;
std::map<int, bool> take;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &x[i], &y[i]);
        map[x[i]]++;
    }
    int sx, sy;
    sx = sy = -1;
    for (const auto &[k, v] : map)
    {
        if (v % 2 == 1)
        {
            sx = k;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        int d = x[i] - sx;
        take[y[i] + d] ^= true;
    }
    for (const auto &[k, v] : take)
    {
        if (v)
        {
            sy = k;
        }
    }
    printf("%d %d\n", sx, sy);
    return 0;
}