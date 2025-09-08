#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <tuple>
#include <vector>
class Inter
{
  public:
    int size;
    std::vector<int> d;
    Inter()
    {
        reset();
    }
    void reset()
    {
        size = 0;
        d.clear();
    }
    void format()
    {
        for (; d.back() == 0;)
        {
            d.pop_back();
        }
        size = d.size();
    }
    std::string to_string() const
    {
        std::string res;
        for (int i = size - 1; i >= 0; i--)
        {
            res += d[i] + '0';
        }
        return res;
    }
    int &operator[](const int &index)
    {
        return d[index];
    }
    int operator[](const int &index) const
    {
        return d[index];
    }
    friend bool operator<(const Inter &x, const Inter &y)
    {
        if (x.size < y.size)
        {
            return true;
        }
        if (x.size > y.size)
        {
            return false;
        }
        for (int i = x.size - 1; i >= 0; i--)
        {
            if (x[i] < y[i])
            {
                return true;
            }
            if (x[i] > y[i])
            {
                return false;
            }
        }
        return false;
    }
    friend bool operator>(const Inter &x, const Inter &y)
    {
        return y < x;
    }
    friend bool operator==(const Inter &x, const Inter &y)
    {
        return !(x < y) && !(x > y);
    }
    friend Inter operator+(const Inter &x, const Inter &y)
    {
        Inter res;
        auto ad = 0;
        for (int i = 0; i < std::max(x.size, y.size) || ad != 0; i++)
        {
            res.d.push_back(((i < x.size ? x[i] : 0) + (i < y.size ? y[i] : 0) + ad) % 10);
            ad = ((i < x.size ? x[i] : 0) + (i < y.size ? y[i] : 0) + ad) / 10;
        }
        res.size = res.d.size();
        return res;
    }
    Inter operator+=(const Inter &x)
    {
        return (*this) = (*this) + x;
    }
};
constexpr int MaxN = 2e5 + 5;
int n, k, d;
char s[MaxN];
bool found;
bool vis[MaxN];
Inter answer;
std::vector<std::tuple<int, int>> v;
Inter take(int l, int r)
{
    Inter res;
    for (int i = r; i >= l; i--)
    {
        res.d.push_back(s[i] - '0');
    }
    res.format();
    return res;
}
void check()
{
    Inter temp;
    for (const auto &[l, r] : v)
    {
        temp += take(l, r);
    }
    if (!found || temp < answer)
    {
        found = true;
        answer = temp;
    }
}
void dfs(int u, int w, int a, int b)
{
    if (w == 0)
    {
        if (a == 0 && b == 0)
        {
            check();
        }
        return;
    }
    auto next = [&](int len) -> void {
        v.push_back({u, u + len - 1});
        dfs(u + len, w - 1, a, b);
        v.pop_back();
    };
    if (s[u] <= '4')
    {
        a++;
        b -= 2;
        next(d + 2);
        a--;
        b += 2;
    }
    a--;
    next(d);
    a++;
    b--;
    next(d + 1);
    b++;
}
void solve()
{
    found = false;
    answer.reset();
    scanf("%d%d", &n, &k);
    scanf("%s", s + 1);
    k++;
    int c = n % k;
    d = n / k;
    if (c == 0)
    {
        c = k;
        d--;
    }
    dfs(1, k, k - c, c);
    printf("%s\n", answer.to_string().c_str());
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