#include <algorithm>
#include <cstdio>
#include <vector>
int n, d;
std::vector<int> v;
int main()
{
    scanf("%d%d", &n, &d);
    for (int i = 1; i <= 2 * n; i++)
    {
        int x;
        scanf("%d", &x);
        v.push_back(x);
    }
    std::sort(v.begin(), v.end());
    for (int i = 0; i < 2 * n; i += 2)
    {
        if (v[i + 1] - v[i] > d)
        {
            printf("No\n");
            return 0;
        }
    }
    printf("Yes\n");
    return 0;
}