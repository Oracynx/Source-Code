#include <cstdio>
int n;
int main()
{
    scanf("%d", &n);
    if (n == 3)
    {
        printf("-3 -3 -3 -2 3 1\n");
        return 0;
    }
    printf("1");
    for (int i = 1; i <= n - 1; i++)
    {
        printf(" 2 -1");
    }
    printf(" %d\n", 3 - n);
    return 0;
}