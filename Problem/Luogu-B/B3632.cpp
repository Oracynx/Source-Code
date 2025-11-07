#include <cstdio>
#include <set>
int n, m;
std::set<int> a;
std::set<int> b;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int x;
        scanf("%d", &x);
        a.insert(x);
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
        int x;
        scanf("%d", &x);
        b.insert(x);
    }
    printf("%zu\n", a.size());
    a.merge(b);
    for (const auto &val : b)
    {
        printf("%d ", val);
    }
    printf("\n");
    for (const auto &val : a)
    {
        printf("%d ", val);
    }
    printf("\n");
    return 0;
}