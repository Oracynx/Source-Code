#include <cstdio>
#include <cstring>
#include <numeric>
#include <vector>
constexpr int MaxN = 3e5 + 5;
constexpr int MaxS = 5e3 + 5;
int n;
int p[MaxN];
int vis[MaxS];
int freq[MaxN];
int freqSuffix[MaxN];
long long Mod;
std::vector<int> prime;
void init()
{
    for (int i = 2; i <= 5e3; i++)
    {
        if (vis[i])
        {
            continue;
        }
        prime.push_back(i);
        for (int j = i * 2; j <= 5e3; j += i)
        {
            vis[j] = true;
        }
    }
}
long long fsp(long long x, long long y)
{
    long long result = 1;
    for (; y != 0;)
    {
        if (y & 1)
        {
            result = result * x % Mod;
        }
        y >>= 1;
        x = x * x % Mod;
    }
    return result;
}
void solve()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
        if (p[i] == 0)
        {
            i--;
            n--;
        }
    }
    for (int i = 1; i <= 5000; i++)
    {
        freq[i] = 0;
        freqSuffix[i] = 0;
    }
    for (int i = 1; i <= n; i++)
    {
        freq[p[i]]++;
    }
    for (int i = 5000; i >= 1; i--)
    {
        freqSuffix[i] = freqSuffix[i + 1] + freq[i];
    }
    long long top = std::accumulate(p + 1, p + 1 + n, 0);
    if (top == 0)
    {
        printf("0\n");
        return;
    }
    long long answer = 1;
    for (const auto &pr : prime)
    {
        long long d = 0;
        long long cp = pr;
        for (; cp <= top;)
        {
            long long c = top / cp;
            long long dv = 0;
            long long cpv = cp;
            for (; cpv <= top;)
            {
                dv += freqSuffix[cpv];
                cpv += cp;
            }
            d += c - dv;
            cp *= pr;
        }
        if (d > 0)
        {
            answer *= fsp(pr, d);
            answer %= Mod;
        }
    }
    printf("%lld\n", answer);
}
int main()
{
    init();
    int t;
    scanf("%d%lld", &t, &Mod);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}