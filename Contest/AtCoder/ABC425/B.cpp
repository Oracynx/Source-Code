#include <algorithm>
#include <cstdio>
#include <numeric>
#include <vector>
int n;
std::vector<int> v;
std::vector<int> f;
int main()
{
    scanf("%d", &n);
    v.resize(n);
    f.resize(n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &v[i]);
    }
    std::iota(f.begin(), f.end(), 1);
    for (;;)
    {
        if ([]() -> bool {
                for (int i = 0; i < n; i++)
                {
                    if (v[i] != f[i] && v[i] != -1)
                    {
                        return false;
                    }
                }
                return true;
            }())
        {
            printf("Yes\n");
            std::for_each(f.begin(), f.end(), [](const int &x) { printf("%d ", x); });
            printf("\n");
            return 0;
        }
        if (!std::next_permutation(f.begin(), f.end()))
        {
            break;
        }
    }
    printf("No\n");
    return 0;
}