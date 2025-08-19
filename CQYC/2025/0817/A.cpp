#include <cstdio>
constexpr int MaxC = 1e1 + 5;
int n;
int cost[MaxC][MaxC];
long long answer;
int getHead(int x)
{
    return x / 10 == 0 ? x : getHead(x / 10);
}
int getTail(int x)
{
    return x % 10;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        cost[getHead(i)][getTail(i)]++;
    }
    for (int i = 1; i <= n; i++)
    {
        answer += cost[getTail(i)][getHead(i)];
    }
    printf("%lld\n", answer);
    return 0;
}