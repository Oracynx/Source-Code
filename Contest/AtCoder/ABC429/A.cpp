#include <cstdio>
int n, m;
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        printf("%s\n", i <= m ? "OK" : "Too Many Requests");
    }
    return 0;
}