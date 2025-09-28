#include <cstdio>
int n;
int answer;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        answer += (i % 2 == 0 ? 1 : -1) * i * i * i;
    }
    printf("%d\n", answer);
    return 0;
}