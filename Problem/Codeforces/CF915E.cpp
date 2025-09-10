#include <cstdio>
#include <set>
#include <tuple>
int n, m;
int answer;
std::set<std::tuple<int, int, bool>> set;
int main()
{
    scanf("%d%d", &n, &m);
    answer = n;
    set.insert({1, n, true});
    for (int i = 1; i <= m; i++)
    {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        auto it = set.upper_bound({l, 0x3f3f3f3f, true});
        it--;
        auto [cl, cr, type] = *it;
        set.erase(it);
        if (type)
        {
            answer -= cr - cl + 1;
        }
        if (cl < l)
        {
            set.insert({cl, l - 1, type});
            if (type)
            {
                answer += (l - 1) - cl + 1;
            }
        }
        if (r < cr)
        {
            set.insert({r + 1, cr, type});
            if (type)
            {
                answer += cr - (r + 1) + 1;
            }
        }
        for (;;)
        {
            auto it = set.lower_bound({l, 0, false});
            if (it == set.end())
            {
                break;
            }
            auto [cl, cr, type] = *it;
            if (r < cl)
            {
                break;
            }
            set.erase(it);
            if (type)
            {
                answer -= cr - cl + 1;
            }
            if (r < cr)
            {
                set.insert({r + 1, cr, type});
                if (type)
                {
                    answer += cr - (r + 1) + 1;
                }
                break;
            }
        }
        set.insert({l, r, k == 2});
        if (k == 2)
        {
            answer += r - l + 1;
        }
        printf("%d\n", answer);
    }
    return 0;
}