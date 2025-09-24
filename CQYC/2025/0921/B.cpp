#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <string>
#include <vector>
constexpr long long Base[2] = {29, 31};
constexpr long long Mod[2] = {975432499, 997543249};
constexpr int MaxN = 5e3 + 5;
long long b[2][26];
long long pb[2][MaxN];
long long ipb[2][MaxN];
class hash
{
  public:
    int len;
    int h[2];
    hash()
    {
        len = 0;
        h[0] = 0;
        h[1] = 0;
    }
    hash(const char &c)
    {
        len = 1;
        h[0] = b[0][c - 'a'];
        h[1] = b[1][c - 'a'];
    }
    hash(const std::string &str)
    {
        (*this) = str.c_str();
    }
    hash(const char *str)
    {
        (*this) = hash();
        int c = strlen(str);
        (*this).len = c;
        for (int i = 0; i < c; i++)
        {
            (*this) = (*this) + str[i];
        }
    }
    friend hash operator+(const hash &x, const hash &y)
    {
        hash res;
        res.h[0] = (1ll * x.h[0] * pb[0][y.len] + y.h[0]) % Mod[0];
        res.h[1] = (1ll * x.h[1] * pb[1][y.len] + y.h[1]) % Mod[1];
        res.len = x.len + y.len;
        return res;
    }
    friend hash operator-(const hash &x, const hash &y)
    {
        hash res;
        res.h[0] = (x.h[0] - 1ll * pb[0][x.len - y.len] * y.h[0] % Mod[0] + Mod[0]) % Mod[0];
        res.h[1] = (x.h[1] - 1ll * pb[1][x.len - y.len] * y.h[1] % Mod[1] + Mod[1]) % Mod[1];
        res.len = x.len - y.len;
        return res;
    }
    friend bool operator==(const hash &x, const hash &y)
    {
        return x.h[0] == y.h[0] /* && x.h[1] == y.h[1] */ && x.len == y.len;
    }
    static long long fsp(long long x, long long y, long long Mod)
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
};
int n, m;
int answer;
int t[MaxN];
int ad[MaxN][MaxN];
int ag[MaxN][MaxN];
char s[MaxN][MaxN];
hash p[MaxN];
hash rp[MaxN];
std::vector<int> v[MaxN];
std::priority_queue<int> queue;
void add(int l, int r, int x)
{
    v[l].push_back(x);
    v[r + 1].push_back(-x);
}
hash query(int l, int r)
{
    if (l <= r)
    {
        return p[r] - p[l - 1];
    }
    else
    {
        return rp[r] - rp[l + 1];
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    int c = std::max(n, m);
    for (int i = 0; i < 26; i++)
    {
        b[0][i] = hash::fsp(Base[0], (i + 7) * Base[0], Mod[0]);
        b[1][i] = hash::fsp(Base[1], (i + 7) * Base[1], Mod[1]);
    }
    pb[0][0] = 1;
    pb[1][0] = 1;
    ipb[0][0] = 1;
    ipb[1][0] = 1;
    for (int i = 1; i <= c; i++)
    {
        pb[0][i] = pb[0][i - 1] * Base[0] % Mod[0];
        pb[1][i] = pb[1][i - 1] * Base[1] % Mod[1];
        ipb[0][i] = hash::fsp(pb[0][i], Mod[0] - 2, Mod[0]);
        ipb[1][i] = hash::fsp(pb[1][i], Mod[1] - 2, Mod[1]);
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", s[i] + 1);
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            p[j] = p[j - 1] + s[i][j];
        }
        for (int j = m; j >= 1; j--)
        {
            rp[j] = rp[j + 1] + s[i][j];
        }
        for (int j = 1; j <= m; j++)
        {
            v[j].clear();
        }
        for (int j = 1; j <= m; j++)
        {
            int l, r;
            l = 1;
            r = std::min(j, m - j);
            int result = 0;
            for (; l <= r;)
            {
                int mid = (l + r) / 2;
                if (query(j, j - mid + 1) == query(j + 1, j + mid))
                {
                    result = mid;
                    l = mid + 1;
                }
                else
                {
                    r = mid - 1;
                }
            }
            if (result >= 1)
            {
                add(j - result + 1, j + result, result * 2);
            }
            l = 1;
            r = std::min(j, m - j - 1);
            result = 0;
            for (; l <= r;)
            {
                int mid = (l + r) / 2;
                if (query(j, j - mid + 1) == query(j + 2, j + mid + 1))
                {
                    result = mid;
                    l = mid + 1;
                }
                else
                {
                    r = mid - 1;
                }
            }
            if (result >= 1)
            {
                add(j - result + 1, j + result + 1, result * 2 + 1);
            }
        }
        for (int j = 1; j <= m; j++)
        {
            t[j] = 0;
        }
        for (; !queue.empty();)
        {
            queue.pop();
        }
        t[0] = 1;
        queue.push(0);
        for (int j = 1; j <= m; j++)
        {
            for (const auto &val : v[j])
            {
                if (val > 0)
                {
                    t[val]++;
                    if (t[val] == 1)
                    {
                        queue.push(val);
                    }
                }
                else
                {
                    t[-val]--;
                }
            }
            for (; t[queue.top()] == 0;)
            {
                queue.pop();
            }
            ad[i][j] = std::max(1, queue.top());
        }
    }
    for (int j = 1; j <= m; j++)
    {
        p[j] = hash();
    }
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            p[j] = p[j - 1] + s[j][i];
        }
        for (int j = n; j >= 1; j--)
        {
            rp[j] = rp[j + 1] + s[j][i];
        }
        for (int j = 1; j <= n; j++)
        {
            v[j].clear();
        }
        for (int j = 1; j <= n; j++)
        {
            int l, r;
            l = 1;
            r = std::min(j, n - j);
            int result = 0;
            for (; l <= r;)
            {
                int mid = (l + r) / 2;
                if (query(j, j - mid + 1) == query(j + 1, j + mid))
                {
                    result = mid;
                    l = mid + 1;
                }
                else
                {
                    r = mid - 1;
                }
            }
            if (result >= 1)
            {
                add(j - result + 1, j + result, result * 2);
            }
            l = 1;
            r = std::min(j, n - j - 1);
            result = 0;
            for (; l <= r;)
            {
                int mid = (l + r) / 2;
                if (query(j, j - mid + 1) == query(j + 2, j + mid + 1))
                {
                    result = mid;
                    l = mid + 1;
                }
                else
                {
                    r = mid - 1;
                }
            }
            if (result >= 1)
            {
                add(j - result + 1, j + result + 1, result * 2 + 1);
            }
        }
        for (int j = 1; j <= n; j++)
        {
            t[j] = 0;
        }
        for (; !queue.empty();)
        {
            queue.pop();
        }
        t[0] = 1;
        queue.push(0);
        for (int j = 1; j <= n; j++)
        {
            for (const auto &val : v[j])
            {
                if (val > 0)
                {
                    t[val]++;
                    if (t[val] == 1)
                    {
                        queue.push(val);
                    }
                }
                else
                {
                    t[-val]--;
                }
            }
            for (; t[queue.top()] == 0;)
            {
                queue.pop();
            }
            ag[j][i] = std::max(1, queue.top());
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            answer = std::max(answer, ad[i][j] * ag[i][j]);
        }
    }
    printf("%d\n", answer);
    return 0;
}