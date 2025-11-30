#include <cstdio>
#include <vector>
constexpr int MaxN = 3e6 + 5;
int n;
int p[MaxN];
int answer[MaxN];
std::vector<int> v;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }
    for (int i = n; i >= 1; i--)
    {
        for (; !v.empty() && p[v.back()] <= p[i];)
        {
            v.pop_back();
        }
        answer[i] = v.empty() ? 0 : v.back();
        v.push_back(i);
    }
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", answer[i]);
    }
    return 0;
}