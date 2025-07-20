#include <algorithm>
#include <cstdio>
constexpr int MaxN = 1e6 + 5;
int n;
int answer;
int cf[MaxN];
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        cf[l]++;
        cf[r + 1]--;
    }
    int x = 0;
    for (int i = 0; i <= 1e6; i++)
    {
        x += cf[i];
        answer = std::max(answer, x);
    }
    printf("%d\n", answer);
    return 0;
}