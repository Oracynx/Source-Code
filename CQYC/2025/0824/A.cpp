#include <algorithm>
#include <cstdio>
constexpr int MaxN = 1e6 + 5;
int n;
int p[MaxN];
int pre[MaxN];
int suf[MaxN];
int npre[MaxN];
int nsuf[MaxN];
long long answer;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        pre[i] = std::max(pre[i - 1], p[i]);
    }
    for (int i = n; i >= 1; i--)
    {
        suf[i] = std::max(suf[i + 1], p[i]);
    }
    answer = 0x3f3f3f3f'3f3f3f3f;
    for (int i = 1; i <= n; i++)
    {
        int cp = p[i];
        p[i] = pre[i - 1];
        for (int i = 1; i <= n; i++)
        {
            npre[i] = std::max(npre[i - 1], p[i]);
        }
        for (int i = n; i >= 1; i--)
        {
            nsuf[i] = std::max(nsuf[i + 1], p[i]);
        }
        long long temp = 0;
        for (int i = 1; i <= n; i++)
        {
            temp += std::max(0, std::min(npre[i - 1], nsuf[i + 1]) - p[i]);
        }
        answer = std::min(answer, temp);
        p[i] = suf[i + 1];
        for (int i = 1; i <= n; i++)
        {
            npre[i] = std::max(npre[i - 1], p[i]);
        }
        for (int i = n; i >= 1; i--)
        {
            nsuf[i] = std::max(nsuf[i + 1], p[i]);
        }
        temp = 0;
        for (int i = 1; i <= n; i++)
        {
            temp += std::max(0, std::min(npre[i - 1], nsuf[i + 1]) - p[i]);
        }
        answer = std::min(answer, temp);
        p[i] = cp;
    }
    printf("%lld\n", answer);
    return 0;
}