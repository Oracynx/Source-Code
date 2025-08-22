#include <cstdio>
constexpr int MaxN = 2e5 + 5;
int n, m;
int s[32][MaxN];
signed int p[MaxN];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%u", &p[i]);
        for (int j = 0; j < 32; j++)
        {
            s[j][i] = s[j][i - 1] + ((p[i] >> j) & 1);
        }
    }
    for (int i = 1; i <= m; i++)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        unsigned int d = r - l + 1;
        unsigned int answer = 0;
        for (int j = 0; j < 32; j++)
        {
            unsigned int u, v;
            u = s[j][r] - s[j][l - 1];
            v = d - u;
            unsigned int c = d * d * d * d;
            c -= v * v * v * v + v * v * v * u + v * v * u * v + v * u * u * u + u * v * u * u + u * u * u * u;
            answer += c * (1u << j);
        }
        printf("%u\n", answer);
    }
    return 0;
}