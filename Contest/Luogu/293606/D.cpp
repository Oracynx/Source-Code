#include <cstdio>
#include <vector>
constexpr int MaxN = 1e7 + 5;
int n;
int p[MaxN];
int ls[MaxN];
int rs[MaxN];
std::vector<int> v;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
        int last = 0;
        for (; !v.empty() && p[v.back()] > p[i];)
        {
            last = v.back();
            v.pop_back();
        }
        if (!v.empty())
        {
            rs[v.back()] = i;
        }
        if (last)
        {
            ls[i] = last;
        }
        v.push_back(i);
    }
    long long answer1, answer2;
    answer1 = answer2 = 0;
    for (int i = 1; i <= n; i++)
    {
        answer1 ^= (long long)(i) * (ls[i] + 1);
        answer2 ^= (long long)(i) * (rs[i] + 1);
    }
    printf("%lld %lld\n", answer1, answer2);
    return 0;
}