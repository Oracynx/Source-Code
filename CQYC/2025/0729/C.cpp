#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <numeric>
#include <string>
#include <tuple>
#include <vector>

// clang-format off

namespace IO
{
	char buff[1<<21],*p1=buff,*p2=buff;
	char getch(){return p1==p2&&(p2=((p1=buff)+fread(buff,1,1<<21,stdin)),p1==p2)?EOF:*p1++;}
	template<typename T>void read(T &x){char ch=getch();int fl=1;x=0;while(ch>'9'||ch<'0'){if(ch=='-')fl=-1;ch=getch();}while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getch();}x*=fl;}
	template<typename T>void read_s(T &x){x="";char ch=getch();while(!(ch>='a'&&ch<='z')&&!(ch>='A'&&ch<='Z'))ch=getch();while((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')){x+=ch;ch=getch();}}
	template<typename T,typename ...Args>void read(T &x,Args& ...args){read(x);read(args...);}
	char obuf[1<<21],*p3=obuf;
	void putch(char ch) {if(p3-obuf<(1<<21))*p3++=ch;else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;}
	char ch[100];
	template<typename T>void write(T x) {if(!x)return putch('0');if(x<0)putch('-'),x*=-1;int top=0;while(x)ch[++top]=x%10+48,x/=10;while(top)putch(ch[top]),top--;}
	template<typename T,typename ...Args>void write(T x,Args ...args) {write(x);putch(' ');write(args...);}
	void put(std::string s){for(int i=0;i<int(s.size());i++)putch(s[i]);}
	void flush(){fwrite(obuf,p3-obuf,1,stdout);}
}
using namespace IO;

// clang-format on

constexpr int MaxN = 5e5 + 5;
constexpr int MaxM = 1e7 + 5;
int rn;
int base;
int n, m, q;
int f[MaxN];
int rl[MaxN];
int *p[MaxN];
int depth[MaxN];
int jump[22][MaxN];
int jump_max[22][MaxN];
unsigned long long fact[MaxN];
unsigned long long answer[MaxN];
std::vector<int> tr;
std::vector<std::tuple<int, int>> g[MaxN];
std::vector<std::tuple<int, int, int>> links;
std::vector<std::tuple<int, int, int, int>> ask;

int index;
int tree[MaxN];
int t_left[MaxM];
int t_right[MaxM];
int t_size[MaxM];
unsigned long long t_sum[MaxM];

int get_new()
{
    return ++index;
}

int get_id(int x, int y)
{
    return (x - 1) * m + y;
}
int find(int x)
{
    return f[x] == x ? x : f[x] = find(f[x]);
}
void merge(int x, int y)
{
    x = find(x);
    y = find(y);
    if (x == y)
    {
        return;
    }
    f[y] = x;
}
void dfs(int u, int f, int d)
{
    depth[u] = depth[f] + 1;
    jump[0][u] = f;
    jump_max[0][u] = d;
    for (int j = 1; j <= 20; j++)
    {
        jump[j][u] = jump[j - 1][jump[j - 1][u]];
        jump_max[j][u] = std::max(jump_max[j - 1][u], jump_max[j - 1][jump[j - 1][u]]);
    }
    for (const auto &[v, w] : g[u])
    {
        if (v == f)
        {
            continue;
        }
        dfs(v, u, w);
    }
}
int find(int u, int v)
{
    if (depth[u] < depth[v])
    {
        std::swap(u, v);
    }
    int result = 0;
    for (int j = 20; j >= 0; j--)
    {
        if (depth[jump[j][u]] >= depth[v])
        {
            result = std::max(result, jump_max[j][u]);
            u = jump[j][u];
        }
    }
    for (int j = 20; j >= 0; j--)
    {
        if (jump[j][u] != jump[j][v])
        {
            result = std::max(result, std::max(jump_max[j][u], jump_max[j][v]));
            u = jump[j][u];
            v = jump[j][v];
        }
    }
    if (u != v)
    {
        result = std::max(result, std::max(jump_max[0][u], jump_max[0][v]));
    }
    return result;
}
void upstream(int c)
{
    if (t_left[c] == 0 && t_right[c] == 0)
    {
        return;
    }
    if (t_left[c] == 0)
    {
        t_sum[c] = t_sum[t_right[c]];
        t_size[c] = t_size[t_right[c]];
        return;
    }
    if (t_right[c] == 0)
    {
        t_sum[c] = t_sum[t_left[c]];
        t_size[c] = t_size[t_left[c]];
        return;
    }
    t_sum[c] = t_sum[t_left[c]] + fact[t_size[t_left[c]]] * t_sum[t_right[c]];
    t_size[c] = t_size[t_left[c]] + t_size[t_right[c]];
}
void change(int c, int s, int t, int x)
{
    if (s == t)
    {
        t_sum[c] += fact[t_size[c]] * tr[s - 1];
        t_size[c]++;
        return;
    }
    int mid = (s + t) / 2;
    if (x <= mid)
    {
        if (t_left[c] == 0)
        {
            t_left[c] = get_new();
        }
        change(t_left[c], s, mid, x);
    }
    else
    {
        if (t_right[c] == 0)
        {
            t_right[c] = get_new();
        }
        change(t_right[c], mid + 1, t, x);
    }
    upstream(c);
}
void t_merge(int c, int f)
{
    if (t_left[c] == 0 && t_right[c] == 0 && t_left[f] == 0 && t_right[f] == 0)
    {
        t_sum[c] += fact[t_size[c]] * t_sum[f];
        t_size[c] += t_size[f];
        return;
    }
    if (t_left[c] == 0)
    {
        t_left[c] = t_left[f];
    }
    else if (t_left[f] != 0)
    {
        t_merge(t_left[c], t_left[f]);
    }
    if (t_right[c] == 0)
    {
        t_right[c] = t_right[f];
    }
    else if (t_right[f] != 0)
    {
        t_merge(t_right[c], t_right[f]);
    }
    upstream(c);
}
int main()
{
    freopen("city.in", "r", stdin);
    freopen("city.out", "w", stdout);
    read(n, m, base);
    for (int i = 0; i <= n + 4; i++)
    {
        p[i] = new int[m + 5];
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            read(p[i][j]);
            tr.push_back(p[i][j]);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (i >= 2)
            {
                links.push_back({abs(p[i][j] - p[i - 1][j]), get_id(i, j), get_id(i - 1, j)});
            }
            if (i >= 2 && j >= 2)
            {
                links.push_back({abs(p[i][j] - p[i - 1][j - 1]), get_id(i, j), get_id(i - 1, j - 1)});
            }
            if (j >= 2)
            {
                links.push_back({abs(p[i][j] - p[i][j - 1]), get_id(i, j), get_id(i, j - 1)});
            }
            if (i <= n - 1 && j >= 2)
            {
                links.push_back({abs(p[i][j] - p[i + 1][j - 1]), get_id(i, j), get_id(i + 1, j - 1)});
            }
        }
    }
    std::sort(tr.begin(), tr.end());
    tr.erase(std::unique(tr.begin(), tr.end()), tr.end());
    rn = tr.size();
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            rl[get_id(i, j)] = std::lower_bound(tr.begin(), tr.end(), p[i][j]) - tr.begin() + 1;
        }
    }
    std::sort(links.begin(), links.end());
    std::iota(f + 1, f + 1 + n * m, 1);
    for (const auto &[w, u, v] : links)
    {
        int fu = find(u);
        int fv = find(v);
        if (fu != fv)
        {
            g[fu].push_back({fv, w});
            g[fv].push_back({fu, w});
            merge(fu, fv);
        }
    }
    dfs(1, 1, 0);
    read(q);
    for (int i = 1; i <= q; i++)
    {
        int op;
        read(op);
        if (op == 1)
        {
            int sx, ex, sy, ey;
            read(sx, ex, sy, ey);
            answer[i] = find(get_id(sx, sy), get_id(ex, ey));
        }
        else if (op == 2)
        {
            int x, y, k;
            read(x, y, k);
            ask.push_back({k, x, y, i});
        }
    }
    fact[0] = 1;
    for (int i = 1; i <= n * m; i++)
    {
        fact[i] = fact[i - 1] * base;
    }
    std::iota(f + 1, f + 1 + n * m, 1);
    for (int i = 1; i <= n * m; i++)
    {
        tree[i] = get_new();
        change(tree[i], 1, rn, rl[i]);
    }
    std::sort(ask.begin(), ask.end());
    auto it = ask.begin();
    for (const auto &[w, u, v] : links)
    {
        for (; it != ask.end(); it++)
        {
            const auto [k, x, y, id] = *it;
            if (w <= k)
            {
                break;
            }
            answer[id] = t_sum[tree[find(get_id(x, y))]];
        }
        if (it == ask.end())
        {
            break;
        }
        int fu = find(u);
        int fv = find(v);
        if (fu != fv)
        {
            if (t_size[tree[fu]] < t_size[tree[fv]])
            {
                std::swap(fu, fv);
            }
            merge(fu, fv);
            t_merge(tree[fu], tree[fv]);
        }
    }
    for (; it != ask.end(); it++)
    {
        const auto [k, x, y, id] = *it;
        answer[id] = t_sum[tree[find(get_id(x, y))]];
    }
    for (int i = 1; i <= q; i++)
    {
        write(answer[i]);
        putch('\n');
    }
    flush();
    return 0;
}