#include <algorithm>
#include <cstdio>
#include <map>
int n;
long long answer;
std::map<int, long long> map;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int x;
        scanf("%d", &x);
        int cp = x;
        for (int j = 2; j <= 1e5; j++)
        {
            if (cp % j == 0)
            {
                map[j] += x;
            }
            for (; cp % j == 0;)
            {
                cp /= j;
            }
        }
        if (cp != 1)
        {
            map[cp] += x;
        }
    }
    for (const auto &[key, value] : map)
    {
        answer = std::max(answer, value);
    }
    printf("%lld\n", answer);
    return 0;
}