#include <cstdio>
#include <set>
#include <tuple>
constexpr int MaxN = 1e5 + 5;
constexpr int MaxM = 1e6 + 5;
int n, m;
int cnt[MaxN];
long long value;
long long a[MaxN];
long long b[MaxN];
long long f[MaxM];
std::set<std::tuple<long long, int>> one;
std::set<std::tuple<long long, int>> two;
std::set<std::tuple<long long, int>> have;
int cost(int u)
{
    return cnt[u] == 0 ? 0 : cnt[u] == 1 || cnt[u] == 3 ? a[u] : b[u];
}
void pop(int u)
{
    if (cnt[u] == 0)
    {
        return;
    }
    if (cnt[u] == 1)
    {
        value -= a[u];
        have.erase({a[u], u});
        one.erase({b[u], u});
        one.insert({a[u], u});
    }
    else if (cnt[u] == 2)
    {
        value -= b[u];
        have.erase({b[u], u});
        have.insert({a[u], u});
        one.erase({a[u], u});
        one.insert({b[u], u});
        two.erase({a[u] + b[u], u});
    }
    else if (cnt[u] == 3)
    {
        value -= a[u];
        have.erase({a[u], u});
        have.insert({b[u], u});
        one.insert({a[u], u});
    }
    cnt[u]--;
}
void take(int u)
{
    if (cnt[u] == 3)
    {
        return;
    }
    cnt[u]++;
    if (cnt[u] == 1)
    {
        value += a[u];
        have.insert({a[u], u});
        one.erase({a[u], u});
        one.insert({b[u], u});
    }
    else if (cnt[u] == 2)
    {
        value += b[u];
        have.erase({a[u], u});
        have.insert({b[u], u});
        one.erase({b[u], u});
        two.erase({b[u] + a[u], u});
        one.insert({a[u], u});
    }
    else if (cnt[u] == 3)
    {
        value += a[u];
        have.erase({b[u], u});
        have.insert({a[u], u});
        one.erase({a[u], u});
    }
}
int who(int nu)
{
    auto it = have.begin();
    for (;;)
    {
        if (std::get<1>(*it) != nu)
        {
            return std::get<1>(*it);
        }
        it++;
        if (it == have.end())
        {
            break;
        }
    }
    return -1;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &b[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        cnt[i] = 0;
        one.insert({a[i], i});
        two.insert({a[i] + b[i], i});
    }
    take(std::get<1>(*one.rbegin()));
    f[1] = value;
    for (int i = 2; i <= m; i++)
    {
        if (one.empty())
        {
            f[i] = f[i - 1];
            continue;
        }
        int w;
        long long c;
        w = -1;
        c = 0;
        auto it = two.end();
        for (int j = 1; j <= 3 && it != two.begin(); j++)
        {
            it--;
            int d = who(std::get<1>(*it));
            if (d == -1)
            {
                continue;
            }
            long long r = std::get<0>(*it) - cost(d);
            if (r > c)
            {
                c = r;
                w = std::get<1>(*it);
            }
        }
        if (c > std::get<0>(*one.rbegin()))
        {
            pop(who(w));
            take(w);
            take(w);
        }
        else
        {
            take(std::get<1>(*one.rbegin()));
        }
        f[i] = value;
    }
    long long answer = 0;
    for (int i = 1; i <= m; i++)
    {
        answer ^= f[i];
    }
    printf("%lld\n", answer);
    return 0;
}