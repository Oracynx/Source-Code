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
        map[x]++;
    }
    for (const auto &[k, v] : map)
    {
        answer += v * (v - 1) * (n - v);
    }
    printf("%lld\n", answer / 2);
    return 0;
}