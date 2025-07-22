#include <algorithm>
#include <cstdio>
#include <tuple>
#include <vector>
constexpr int MaxN = 1e3 + 5;
int n;
int p[MaxN];
int w[MaxN];
int ref[MaxN];
std::vector<std::tuple<int, int>> v;
std::vector<std::tuple<int, int>> methods;
void change(int op, int x)
{
    if (op == 1)
    {
        for (int i = 1; i <= n; i++)
        {
            if (p[i] == x)
            {
                p[i]++;
            }
        }
    }
    else if (op == 2)
    {
        p[x]++;
    }
    methods.push_back({op, op == 1 ? x : ref[x]});
}
void solve(int l, int r)
{
    for (; p[l] == w[l] && l <= r;)
    {
        l++;
    }
    if (l > r)
    {
        return;
    }
    if (l == r)
    {
        for (; p[l] < w[l];)
        {
            change(2, l);
        }
        return;
    }
    int mid = (l + r) / 2;
    int can = w[mid + 1] - p[mid + 1] - 1;
    for (int i = mid + 1; i <= r; i++)
    {
        change(2, i);
    }
    for (int i = 1; i <= can; i++)
    {
        change(1, p[mid + 1]);
    }
    solve(mid + 1, r);
    solve(l, mid);
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int x;
        scanf("%d", &x);
        v.push_back({x, i});
    }
    std::sort(v.begin(), v.end());
    int cnt = 0;
    for (const auto &[x, i] : v)
    {
        cnt++;
        w[cnt] = x;
        ref[cnt] = i;
    }
    solve(1, n);
    printf("%zu\n", methods.size());
    for (const auto &[op, x] : methods)
    {
        printf("%d %d\n", op, x);
    }
    return 0;
}