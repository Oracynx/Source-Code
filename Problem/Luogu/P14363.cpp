#include <cctype>
#include <cstdio>
#include <cstring>
#include <queue>
#include <tuple>
#include <vector>
class tnode
{
  public:
    int x;
    tnode *left, *right;
    tnode()
    {
        x = 0;
        left = nullptr;
        right = nullptr;
    }
};
class node
{
  public:
    bool cache_ok;
    node *fa;
    node *fail;
    tnode *tr;
    std::vector<int> end;
    std::tuple<char, char> by;
    std::vector<std::tuple<char, node *>> g[26];
    std::vector<std::tuple<std::tuple<char, char>, node *>> cache;
    node(node *_fa = nullptr, std::tuple<char, char> _by = {'\0', '\0'})
    {
        fa = _fa;
        cache_ok = false;
        tr = nullptr;
        fail = nullptr;
        by = _by;
    }
    node *to(const std::tuple<char, char> &key) const
    {
        const auto &[ka, kb] = key;
        for (const auto &[k, v] : g[ka - 'a'])
        {
            if (k == kb)
            {
                return v;
            }
        }
        return nullptr;
    }
    void set(const std::tuple<char, char> &key, node *value)
    {
        const auto &[ka, kb] = key;
        for (auto &[k, v] : g[ka - 'a'])
        {
            if (k == kb)
            {
                v = value;
            }
        }
        g[ka - 'a'].push_back({kb, value});
    }
    std::vector<std::tuple<std::tuple<char, char>, node *>> &range()
    {
        if (cache_ok)
        {
            return cache;
        }
        cache_ok = true;
        cache.clear();
        for (int ka = 0; ka < 26; ka++)
        {
            for (const auto &[k, v] : g[ka])
            {
                cache.push_back({{'a' + ka, k}, v});
            }
        }
        return cache;
    }
};
constexpr int MaxN = 5e6 + 5;
int n, m;
char s[2][MaxN];
node *root;
node *troot;
void build(tnode *c, int s, int t)
{
    if (s == t)
    {
        return;
    }
    int mid = (s + t) / 2;
    c->left = new tnode();
    c->right = new tnode();
    build(c->left, s, mid);
    build(c->right, mid + 1, t);
}
void change(tnode *p, tnode *c, int s, int t, int w)
{
    if (s == t)
    {
        c->x = p->x + 1;
        return;
    }
    int mid = (s + t) / 2;
    if (w <= mid)
    {
        c->left = new tnode();
        c->right = p->right;
        change(p->left, c->left, s, mid, w);
    }
    else
    {
        c->left = p->left;
        c->right = new tnode();
        change(p->right, c->right, mid + 1, t, w);
    }
    c->x = c->left->x + c->right->x;
}
int query(tnode *c, int s, int t, int l, int r)
{
    if (l <= s && t <= r)
    {
        return c->x;
    }
    int result = 0;
    int mid = (s + t) / 2;
    if (l <= mid)
    {
        result += query(c->left, s, mid, l, r);
    }
    if (r > mid)
    {
        result += query(c->right, mid + 1, t, l, r);
    }
    return result;
}
void add(node *cur, char *a, char *b, int len)
{
    if (*a == '\0')
    {
        cur->end.push_back(len);
        return;
    }
    char ka, kb;
    ka = *a;
    kb = *b;
    a++;
    b++;
    if (cur->to({ka, kb}) == nullptr)
    {
        cur->set({ka, kb}, new node(cur, {ka, kb}));
    }
    add(cur->to({ka, kb}), a, b, len);
}
void build(node *root)
{
    std::queue<node *> queue;
    root->fail = root;
    for (const auto &[k, v] : root->range())
    {
        v->fail = root;
        for (const auto &[ck, cv] : v->range())
        {
            queue.push(cv);
        }
    }
    for (; !queue.empty();)
    {
        auto cur = queue.front();
        queue.pop();
        auto cp = cur->fa->fail;
        for (;;)
        {
            auto next = cp->to(cur->by);
            if (next != nullptr)
            {
                cur->fail = next;
                break;
            }
            if (cp == root)
            {
                cur->fail = root;
                break;
            }
            cp = cp->fail;
        }
        for (const auto &[k, v] : cur->range())
        {
            queue.push(v);
        }
    }
}
node *next(node *cur, std::tuple<char, char> key)
{
    auto cp = cur;
    for (;;)
    {
        auto to = cp->to(key);
        if (to != nullptr)
        {
            return to;
        }
        if (cp == root)
        {
            break;
        }
        cp = cp->fail;
    }
    return root;
}
void tbuild(node *root)
{
    std::queue<node *> queue;
    root->tr = new tnode();
    build(root->tr, 1, 2e5);
    for (const auto &[k, v] : root->range())
    {
        queue.push(v);
    }
    for (; !queue.empty();)
    {
        auto cur = queue.front();
        queue.pop();
        cur->tr = cur->fail->tr;
        for (const auto &val : cur->end)
        {
            auto cp = new tnode();
            change(cur->tr, cp, 1, 2e5, val);
            cur->tr = cp;
        }
        for (const auto &[k, v] : cur->range())
        {
            queue.push(v);
        }
    }
}
int main()
{
    root = new node();
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf(" ");
        for (int j = 0;; j++)
        {
            s[0][j] = getchar();
            if (!std::isalpha(s[0][j]))
            {
                s[0][j] = '\0';
                break;
            }
        }
        scanf(" ");
        for (int j = 0;; j++)
        {
            s[1][j] = getchar();
            if (!std::isalpha(s[1][j]))
            {
                s[1][j] = '\0';
                break;
            }
        }
        int len = strlen(s[0]);
        add(root, s[0], s[1], len);
    }
    build(root);
    tbuild(root);
    for (int i = 1; i <= m; i++)
    {
        scanf(" ");
        for (int j = 0;; j++)
        {
            s[0][j] = getchar();
            if (!std::isalpha(s[0][j]))
            {
                s[0][j] = '\0';
                break;
            }
        }
        scanf(" ");
        for (int j = 0;; j++)
        {
            s[1][j] = getchar();
            if (!std::isalpha(s[1][j]))
            {
                s[1][j] = '\0';
                break;
            }
        }
        node *cur = root;
        int len = strlen(s[0]);
        int pre, aft;
        pre = -1;
        aft = len;
        for (int j = 0; j < len; j++)
        {
            if (s[0][j] != s[1][j])
            {
                break;
            }
            pre++;
        }
        for (int j = len - 1; j >= 0; j--)
        {
            if (s[0][j] != s[1][j])
            {
                break;
            }
            aft--;
        }
        long long answer = 0;
        for (int j = 0; j < len; j++)
        {
            cur = next(cur, {s[0][j], s[1][j]});
            if (j >= aft - 1)
            {
                int l, r;
                l = pre + 1;
                r = j;
                int len = r - l + 1;
                answer += query(cur->tr, 1, 2e5, len, 2e5);
            }
        }
        printf("%lld\n", answer);
    }
    return 0;
}
