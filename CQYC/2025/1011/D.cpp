#include <cstdio>
#include <random>
std::mt19937_64 rnd;
constexpr int MaxN = 4e5 + 5;
constexpr int MaxK = 65;
int n, k;
unsigned long long Mod;
unsigned long long seed;
unsigned long long answer;
unsigned long long p[MaxN];
unsigned long long f[MaxK][25];
int main()
{
    scanf("%d%llu%d", &n, &seed, &k);
    rnd.seed(seed);
    Mod = k == 64 ? -1ull : 1ull << k;
    for (int i = 1; i <= n; i++)
    {
        p[i] = rnd() % Mod;
    }
    for (int j = 0; j < k; j++)
    {
        f[j][0] = 1;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            if (~(p[i] >> j) & 1)
            {
                continue;
            }
            answer +=
                (f[j][4] + f[j][6] + f[j][9] + f[j][11] + f[j][15] + f[j][17] + f[j][20] + f[j][22]) * (1ull << j);
        }
        for (int j = 0; j < k; j++)
        {
            if ((p[i] >> j) & 1)
            {
                f[j][4] += f[j][3];
                f[j][20] += f[j][19];

                f[j][5] += f[j][2];
                f[j][10] += f[j][7];
                f[j][16] += f[j][13];
                f[j][21] += f[j][18];

                f[j][7] += f[j][1];
                f[j][18] += f[j][12];

                f[j][12] += f[j][0];
            }
            else
            {
                f[j][6] += f[j][5];
                f[j][9] += f[j][8];
                f[j][11] += f[j][10];
                f[j][15] += f[j][14];
                f[j][17] += f[j][16];
                f[j][22] += f[j][21];

                f[j][3] += f[j][2];
                f[j][8] += f[j][7];
                f[j][14] += f[j][13];
                f[j][19] += f[j][18];

                f[j][2] += f[j][1];
                f[j][13] += f[j][12];

                f[j][1] += f[j][0];
            }
        }
    }
    printf("%llu\n", answer);
    return 0;
}