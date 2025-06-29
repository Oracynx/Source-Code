#include <cstdio>
#include <set>
int n;
std::multiset<int> set;
void solve()
{
    set.clear();
    scanf("%d", &n);
    int begin, end;
    begin = end = 0;
    for (int i = 1; i <= n; i++)
    {
        int x;
        scanf("%d", &x);
        if (begin == 0)
        {
            begin = x;
        }
        end = x;
        set.insert(x);
    }
    set.erase(set.find(begin));
    set.erase(set.find(end));
    int cur = begin;
    for (int i = 2; i <= n; i++)
    {
        cur *= 2;
        if (end <= cur)
        {
            printf("%d\n", i);
            return;
        }
        auto it = set.upper_bound(cur);
        if (it == set.begin())
        {
            break;
        }
        it--;
        cur = *it;
        set.erase(set.find(cur));
    }
    printf("-1\n");
}
int main()
{
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}