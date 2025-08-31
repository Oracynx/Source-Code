#include <cstdio>
int n, k;
int dfs(int n, int k)
{
    if (n < k)
    {
        return 0;
    }
    if (k == 1 || n == k)
    {
        return 1;
    }
    return dfs(n - k, k) + dfs(n - 1, k - 1);
}
int main()
{
    scanf("%d%d", &n, &k);
    printf("%d", dfs(n, k));
    return 0;
}