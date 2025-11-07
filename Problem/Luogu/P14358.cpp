#include <algorithm>
#include <cstdio>
#include <vector>
int n, m;
std::vector<int> v;
int main()
{
    scanf("%d%d", &n, &m);
    v.resize(n * m);
    for (int i = 0; i < n * m; i++)
    {
        scanf("%d", &v[i]);
    }
    int c = v[0];
    std::sort(v.begin(), v.end());
    int u = std::lower_bound(v.begin(), v.end(), c) - v.begin();
    u = n * m - u - 1;
    printf("%d %d\n", u / n + 1, u / n % 2 == 0 ? u % n + 1 : n - u % n);
    return 0;
}