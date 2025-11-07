#include <algorithm>
#include <cctype>
#include <cstdio>
#include <functional>
#include <vector>
std::vector<int> v;
int main()
{
    for (;;)
    {
        char ch = getchar();
        if (ch == '\n' || ch == EOF)
        {
            break;
        }
        if (std::isdigit(ch))
        {
            v.push_back(ch - '0');
        }
    }
    std::sort(v.begin(), v.end(), std::greater<>());
    for (const auto &val : v)
    {
        printf("%d", val);
    }
    printf("\n");
    return 0;
}