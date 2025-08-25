#include <algorithm>
#include <cstdio>
#include <vector>
constexpr int MaxN = 5e3 + 5;
constexpr long long Mod = 998'244'353;
int n, m;
int p[MaxN];
int pf[MaxN][MaxN];
int treeA[MaxN];
int treeB[MaxN];
int treeC[MaxN];
std::vector<int> va;
std::vector<int> vb;
std::vector<int> vc;
int f(int l, int r)
{
    return pf[l][r];
}
void changeA(int x, int val = 1)
{
    for (; x <= n; x += x & -x)
    {
        treeA[x] += val;
    }
}
void changeB(int x, int val = 1)
{
    for (; x <= n; x += x & -x)
    {
        treeB[x] += val;
    }
}
void changeC(int x, int val = 1)
{
    for (; x <= n; x += x & -x)
    {
        treeC[x] += val;
    }
}
int queryA(int x)
{
    int result = 0;
    for (; x >= 1; x -= x & -x)
    {
        result += treeA[x];
    }
    return result;
}
int queryB(int x)
{
    int result = 0;
    for (; x >= 1; x -= x & -x)
    {
        result += treeB[x];
    }
    return result;
}
int queryC(int x)
{
    int result = 0;
    for (; x >= 1; x -= x & -x)
    {
        result += treeC[x];
    }
    return result;
}
int queryA(int l, int r)
{
    if (l > r)
    {
        return 0;
    }
    if (l == 0)
    {
        l = 1;
    }
    return queryA(r) - queryA(l - 1);
}
int queryB(int l, int r)
{
    if (l > r)
    {
        return 0;
    }
    if (l == 0)
    {
        l = 1;
    }
    return queryB(r) - queryB(l - 1);
}
int queryC(int l, int r)
{
    if (l > r)
    {
        return 0;
    }
    if (l == 0)
    {
        l = 1;
    }
    return queryC(r) - queryC(l - 1);
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        int c = 0;
        for (int j = i; j <= n; j++)
        {
            c = std::max(c, p[j]);
            pf[i][j] = c;
        }
    }
    for (int i = 1; i <= m; i++)
    {
        char ch = '\0';
        scanf(" %c", &ch);
        int x;
        scanf("%d", &x);
        if (ch == 'A')
        {
            va.push_back(x);
            changeA(x);
        }
        else if (ch == 'B')
        {
            vb.push_back(x);
            changeB(x);
        }
        else if (ch == 'C')
        {
            vc.push_back(x);
            changeC(x);
        }
        long long answer = 0;
        for (const auto &l : va)
        {
            for (const auto &r : vb)
            {
                if (l <= r)
                {
                    int c = queryC(l, r);
                    answer += c * f(l, r);
                }
                else
                {
                    int c = queryC(r, l);
                    answer += c * f(r, l);
                }
            }
        }
        for (const auto &l : va)
        {
            for (const auto &r : vc)
            {
                if (l <= r)
                {
                    int c = queryB(l, r - 1);
                    answer += c * f(l, r);
                }
                else
                {
                    int c = queryB(r + 1, l);
                    answer += c * f(r, l);
                }
            }
        }
        for (const auto &l : vb)
        {
            for (const auto &r : vc)
            {
                if (l <= r)
                {
                    int c = queryA(l + 1, r - 1);
                    answer += c * f(l, r);
                }
                else
                {
                    int c = queryA(r + 1, l - 1);
                    answer += c * f(r, l);
                }
            }
        }
        printf("%lld\n", answer % Mod);
    }
    return 0;
}