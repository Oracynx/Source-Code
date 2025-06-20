#include <cstdio>
#include <cstdlib>
constexpr int Rounds = 10;
constexpr int Players = 10;
constexpr int Cards = 5;
struct card
{
    int p;
    int s;
    int f;
    card()
    {
        p = 0;
        s = 0;
        f = 0;
    }
    card(int _p, int _s, int _f)
    {
        p = _p;
        s = _s;
        f = _f;
    }
};
int ks[Players];
int ws[Players];
long long score[Players];
card hand[Players][Cards];
void calc(const card c[Cards], int &k, int &w)
{
    int pts[Cards];
    for (int i = 0; i < Cards; i++)
    {
        pts[i] = c[i].p;
    }
    k = 0;
    bool suc = false;
    for (int i = 0; i < Cards && !suc; i++)
    {
        for (int j = i + 1; j < Cards && !suc; j++)
        {
            for (int t = j + 1; t < Cards && !suc; t++)
            {
                if ((pts[i] + pts[j] + pts[t]) % 10 == 0)
                {
                    int sum = 0;
                    for (int x = 0; x < Cards; x++)
                    {
                        sum += pts[x];
                    }
                    int rem = sum - (pts[i] + pts[j] + pts[t]);
                    int v = rem % 10;
                    k = v == 0 ? 10 : v;
                    suc = true;
                }
            }
        }
    }
    if (!suc)
    {
        k = 0;
    }
    if (k <= 6)
    {
        w = 1;
    }
    else if (k <= 9)
    {
        w = 2;
    }
    else
    {
        bool allKill = true;
        int flowerCnt = 0;
        for (int i = 0; i < Cards; i++)
        {
            if (c[i].p != 10)
            {
                allKill = false;
                break;
            }
            if (c[i].f >= 2)
            {
                flowerCnt++;
            }
        }
        if (allKill)
        {
            if (flowerCnt == 5)
            {
                w = 20;
            }
            else if (flowerCnt == 4)
            {
                w = 10;
            }
            else
            {
                w = 5;
            }
        }
        else
        {
            w = 3;
        }
    }
}
bool generate(const card a[Cards], const card b[Cards])
{
    int ka, kb, wa, wb;
    calc(a, ka, wa);
    calc(b, kb, wb);
    if (ka != kb)
    {
        return ka > kb;
    }
    card ca = a[0], cb = b[0];
    for (int i = 1; i < Cards; i++)
    {
        card x = a[i];
        if (x.p > ca.p || (x.p == ca.p && (x.p == 10 ? (x.f > ca.f || (x.f == ca.f && x.s > ca.s)) : (x.s > ca.s))))
        {
            ca = x;
        }
        x = b[i];
        if (x.p > cb.p || (x.p == cb.p && (x.p == 10 ? (x.f > cb.f || (x.f == cb.f && x.s > cb.s)) : (x.s > cb.s))))
        {
            cb = x;
        }
    }
    if (ca.p != cb.p)
    {
        return ca.p > cb.p;
    }
    if (ca.p == 10 && ca.f != cb.f)
    {
        return ca.f > cb.f;
    }
    return ca.s > cb.s;
}
int main()
{
    for (int r = 0; r < Rounds; r++)
    {
        for (int i = 0; i < Players; i++)
        {
            for (int j = 0; j < Cards; j++)
            {
                char vs[3], ss[2];
                scanf("%2s %1s", vs, ss);
                int p;
                if (vs[0] == 'A')
                {
                    p = 1;
                }
                else if (vs[0] == 'J' || vs[0] == 'Q' || vs[0] == 'K')
                {
                    p = 10;
                }
                else
                {
                    p = atoi(vs);
                }
                int s = ss[0] == 'B' ? 4 : ss[0] == 'R' ? 3 : ss[0] == 'F' ? 2 : 1;
                int f = vs[0] == 'J' ? 2 : vs[0] == 'Q' ? 3 : vs[0] == 'K' ? 4 : vs[0] == '1' ? 1 : 0;
                hand[i][j] = {p, s, f};
            }
        }
        int cp = r;
        for (int i = 0; i < Players; i++)
        {
            calc(hand[i], ks[i], ws[i]);
        }
        for (int i = 0; i < Players; i++)
        {
            if (i != cp)
            {
                bool win = generate(hand[i], hand[cp]);
                int w = win ? ws[i] : ws[cp];
                score[i] += win ? w : -w;
                score[cp] -= win ? w : -w;
            }
        }
    }
    for (int i = 0; i < Players; i++)
    {
        printf("%lld ", score[i]);
    }
    printf("\n");
    return 0;
}
