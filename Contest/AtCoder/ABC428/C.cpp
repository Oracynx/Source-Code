#include <cstdio>
#include <vector>
int n;
std::vector<char> v;
int main()
{
    scanf("%d", &n);
    int c, d;
    c = d = 0;
    for (int i = 1; i <= n; i++)
    {
        int op;
        scanf("%d", &op);
        if (op == 1)
        {
            char ch;
            scanf(" %c", &ch);
            d += ch == '(' ? 1 : -1;
            c += d < 0 ? 1 : 0;
            v.push_back(ch);
        }
        else
        {
            char ch = v.back();
            v.pop_back();
            c -= d < 0 ? 1 : 0;
            d += ch == '(' ? -1 : 1;
        }
        printf("%s\n", d == 0 && c == 0 ? "Yes" : "No");
    }
    return 0;
}