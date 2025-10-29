#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
int n, k;
std::string s;
std::vector<std::string> v;
int find(std::string d)
{
    int c = 0;
    for (int i = 1; i + k - 1 <= n; i++)
    {
        if (s.substr(i, k) == d)
        {
            c++;
        }
    }
    return c;
}
int main()
{
    scanf("%d%d", &n, &k);
    std::cin >> s;
    s = " " + s;
    int best = 0;
    for (int i = 1; i + k - 1 <= n; i++)
    {
        std::string d = s.substr(i, k);
        int c = find(d);
        if (c > best)
        {
            best = c;
            v.clear();
        }
        if (c == best)
        {
            v.push_back(d);
        }
    }
    std::sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(), v.end()), v.end());
    printf("%d\n", best);
    for (const auto &str : v)
    {
        printf("%s ", str.c_str());
    }
    printf("\n");
    return 0;
}