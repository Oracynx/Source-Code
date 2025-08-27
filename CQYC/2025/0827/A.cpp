#include <algorithm>
#include <cctype>
#include <cstdio>
#include <functional>
#include <vector>
constexpr int MaxN = 2e5 + 5;
int n, m;
long long c[MaxN];
std::vector<long long> v;
template <typename _Tp> void read(_Tp &x)
{
    x = 0;
    bool f = false;
    char ch = '\0';
    for (; !std::isdigit(ch);)
    {
        ch = getchar();
        if (ch == '-')
        {
            f = true;
        }
    }
    for (; isdigit(ch);)
    {
        x = x * 10 + (ch ^ 48);
        ch = getchar();
    }
    x = f ? -x : x;
}
void solve()
{
    v.clear();
    read(n);
    read(m);
    n *= 2;
    for (int i = 1; i <= n; i++)
    {
        read(c[i]);
        c[i] *= 2;
    }
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        read(u);
        read(v);
        read(w);
        c[u] += w;
        c[v] += w;
    }
    for (int i = 1; i <= n; i++)
    {
        v.push_back(c[i]);
    }
    std::sort(v.begin(), v.end(), std::greater<>());
    long long answer = 0;
    for (int i = 0; i < n; i++)
    {
        answer += i < n / 2 ? v[i] : -v[i];
    }
    printf("%lld\n", answer / 2);
}
int main()
{
    int t;
    scanf("%*d%d", &t);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}