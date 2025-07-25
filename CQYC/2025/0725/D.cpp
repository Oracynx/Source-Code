#include <cstdio>
constexpr int MaxN = 6e5 + 5;
constexpr long long Mod = 998'244'353;
int type;
int n, q;
long long tree[MaxN];
void change(int x, long long val)
{
    for (; x <= n; x += x & -x)
    {
        tree[x] += val;
    }
}
long long query(int x)
{
    long long result = 0;
    for (; x >= 1; x -= x & -x)
    {
        result += tree[x];
    }
    return result % Mod;
}
long long query(int l, int r)
{
    return (query(r) - query(l - 1) + Mod) % Mod;
}
int main()
{
    scanf("%d", &type);
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
    {
        int x;
        scanf("%d", &x);
        change(i, x);
    }
    long long last_answer = 0;
    for (int i = 1; i <= q; i++)
    {
        int op;
        scanf("%d", &op);
        if (op == 1)
        {
            long long l, r, x;
            scanf("%lld%lld%lld", &l, &r, &x);
            l ^= last_answer * type;
            r ^= last_answer * type;
            x ^= last_answer * type;
            for (int i = l; i <= r; i++)
            {
                change(i, x);
            }
        }
        else if (op == 2)
        {
            long long l, r;
            scanf("%lld%lld", &l, &r);
            l ^= last_answer * type;
            r ^= last_answer * type;
            long long answer = 0;
            for (int cl = l; cl <= r; cl++)
            {
                for (int cr = cl; cr <= r; cr++)
                {
                    answer += query(cl, cr) * query(cl, cr) % Mod +
                              (r - l + 2) * (cr - cl) % Mod * query(cl, cl) % Mod * query(cr, cr) % Mod;
                    answer %= Mod;
                }
            }
            printf("%lld\n", answer);
            last_answer = answer;
        }
    }
    return 0;
}