#include <cstdio>
#include <random>
#include <tuple>
std::mt19937 rnd(std::random_device{}());
class node
{
  public:
    int x;
    int prio;
    int size;
    node *left;
    node *right;
    node()
    {
        x = 0;
        prio = rnd();
        size = 1;
        left = nullptr;
        right = nullptr;
    }
    void upstream()
    {
        size = 1 + (left == nullptr ? 0 : left->size) + (right == nullptr ? 0 : right->size);
    }
};
int n;
node *root;
node *merge(node *l, node *r)
{
    if (l == nullptr)
    {
        return r;
    }
    if (r == nullptr)
    {
        return l;
    }
    if (l->prio < r->prio)
    {
        l->right = merge(l->right, r);
        l->upstream();
        return l;
    }
    else
    {
        r->left = merge(l, r->left);
        r->upstream();
        return r;
    }
}
std::tuple<node *, node *> split(node *c, int x)
{
    if (c == nullptr)
    {
        return {nullptr, nullptr};
    }
    if (c->x <= x)
    {
        auto [l, r] = split(c->right, x);
        c->right = l;
        c->upstream();
        return {c, r};
    }
    else
    {
        auto [l, r] = split(c->left, x);
        c->left = r;
        c->upstream();
        return {l, c};
    }
}
std::tuple<node *, node *> splitRank(node *c, int rk)
{
    if (c == nullptr)
    {
        return {nullptr, nullptr};
    }
    int leftSize = (c->left == nullptr ? 0 : c->left->size) + 1;
    if (leftSize <= rk)
    {
        auto [l, r] = splitRank(c->right, rk - leftSize);
        c->right = l;
        c->upstream();
        return {c, r};
    }
    else
    {
        auto [l, r] = splitRank(c->left, rk);
        c->left = r;
        c->upstream();
        return {l, c};
    }
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int op, x;
        scanf("%d%d", &op, &x);
        if (op == 0)
        {
            auto c = new node;
            c->x = x;
            auto [l, r] = split(root, x);
            root = merge(merge(l, c), r);
        }
        else if (op == 1)
        {
            auto [t, r] = split(root, x);
            auto [l, m] = split(t, x - 1);
            auto [x, y] = splitRank(m, 1);
            delete x;
            root = merge(merge(l, y), r);
        }
        else if (op == 2)
        {
            auto [l, t] = splitRank(root, x - 1);
            auto [m, r] = splitRank(t, 1);
            printf("%d\n", m->x);
            root = merge(merge(l, m), r);
        }
        else if (op == 3)
        {
            auto [l, r] = split(root, x - 1);
            printf("%d\n", l == nullptr ? 0 : l->size);
            root = merge(l, r);
        }
        else if (op == 4)
        {
            auto [t, r] = split(root, x - 1);
            if (t == nullptr)
            {
                printf("-1\n");
                root = merge(t, r);
                continue;
            }
            auto [l, m] = splitRank(t, t->size - 1);
            printf("%d\n", m == nullptr ? -1 : m->x);
            root = merge(merge(l, m), r);
        }
        else if (op == 5)
        {
            auto [l, t] = split(root, x);
            if (t == nullptr)
            {
                printf("-1\n");
                root = merge(l, t);
                continue;
            }
            auto [m, r] = splitRank(t, 1);
            printf("%d\n", m == nullptr ? -1 : m->x);
            root = merge(merge(l, m), r);
        }
    }
    return 0;
}