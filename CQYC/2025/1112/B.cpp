#include <algorithm>
#include <cstdio>
constexpr int MaxN = 1e6 + 5;
class node
{
  public:
    int bw;
    int ch;
    int has;
    int dep;
    node *fa;
    node *to[2];
    node()
    {
        bw = 0;
        ch = 0;
        dep = 0;
        fa = nullptr;
        to[0] = nullptr;
        to[1] = nullptr;
    }
    node(node *from)
    {
        bw = 0;
        ch = 0;
        dep = from->dep + 1;
        fa = from;
        to[0] = nullptr;
        to[1] = nullptr;
    }
    void upstream()
    {
        if (!to[0] && !to[1])
        {
            bw = dep + 2;
            ch = 0;
        }
        else if (!to[0] || !to[1])
        {
            bw = dep + 1;
            ch = to[0] ? 1 : 0;
        }
        else
        {
            bw = std::min(to[0]->bw, to[1]->bw);
            ch = to[0]->bw < to[1]->bw ? 0 : 1;
        }
    }
};
int n;
int answer;
char s[MaxN];
node *root;
void add(node *cur, char *s)
{
    if (*s == '\0')
    {
        cur->has++;
        return;
    }
    int c = *s - '0';
    s++;
    if (!cur->to[c])
    {
        cur->to[c] = new node(cur);
    }
    add(cur->to[c], s);
    cur->upstream();
}
void init(node *cur)
{
    if ((!cur->to[0] ^ !cur->to[1]) && cur->has >= 1)
    {
        if (!cur->to[0] && cur->has >= 1)
        {
            answer++;
            cur->has--;
            cur->to[0] = new node(cur);
            cur->to[0]->has++;
            cur->to[0]->upstream();
        }
        if (!cur->to[1] && cur->has >= 1)
        {
            answer++;
            cur->has--;
            cur->to[1] = new node(cur);
            cur->to[1]->has++;
            cur->to[1]->upstream();
        }
    }
    if (cur->to[0])
    {
        init(cur->to[0]);
    }
    if (cur->to[1])
    {
        init(cur->to[1]);
    }
    cur->upstream();
}
void find(node *cur)
{
    if (!cur->to[0] && !cur->to[1])
    {
        answer += 2;
        cur->has--;
        cur->to[0] = new node(cur);
        cur->to[0]->has++;
        cur->to[0]->upstream();
        cur->to[1] = new node(cur);
        cur->to[1]->has++;
        cur->to[1]->upstream();
    }
    else if (!cur->to[0] || !cur->to[1])
    {
        answer++;
        if (!cur->to[0])
        {
            cur->to[0] = new node(cur);
            cur->to[0]->has++;
            cur->to[0]->upstream();
        }
        else
        {
            cur->to[1] = new node(cur);
            cur->to[1]->has++;
            cur->to[1]->upstream();
        }
    }
    else
    {
        answer++;
        find(cur->to[cur->ch]);
    }
    cur->upstream();
}
void dfs(node *cur)
{
    if (cur->to[0])
    {
        dfs(cur->to[0]);
    }
    if (cur->to[1])
    {
        dfs(cur->to[1]);
    }
    cur->upstream();
    if (!cur->to[0] && !cur->to[1] && cur->has == 1)
    {
        return;
    }
    for (; cur->has >= 1;)
    {
        find(cur);
        cur->has--;
    }
    cur->upstream();
}
int main()
{
    root = new node;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf(" %s", s);
        add(root, s);
    }
    init(root);
    dfs(root);
    printf("%d\n", answer);
    return 0;
}