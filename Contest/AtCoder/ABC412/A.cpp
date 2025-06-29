#include <cstdio>
int n;
int answer;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        answer += b > a ? 1 : 0;
    }
    printf("%d\n", answer);
    return 0;
}