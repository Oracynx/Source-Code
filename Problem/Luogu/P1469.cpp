#include <cstdio>
int n;
int answer;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int x;
        scanf("%d", &x);
        answer ^= x;
    }
    printf("%d\n", answer);
    return 0;
}