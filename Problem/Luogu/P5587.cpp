#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>
constexpr int MaxN = 1e4 + 5;
int n;
int correct;
std::string s[MaxN];
std::string t[MaxN];
int main()
{
    for (;;)
    {
        n++;
        std::getline(std::cin, s[n]);
        if (s[n] == "EOF")
        {
            break;
        }
        std::string temp;
        for (int i = 0; i < int(s[n].size()); i++)
        {
            if (s[n][i] == '<')
            {
                if (!temp.empty())
                {
                    temp.pop_back();
                }
            }
            else
            {
                temp.push_back(s[n][i]);
            }
        }
        s[n] = temp;
    }
    n--;
    for (int i = 1;; i++)
    {
        std::getline(std::cin, t[i]);
        if (t[i] == "EOF")
        {
            break;
        }
        std::string temp;
        for (int j = 0; j < int(t[i].size()); j++)
        {
            if (t[i][j] == '<')
            {
                if (!temp.empty())
                {
                    temp.pop_back();
                }
            }
            else
            {
                temp.push_back(t[i][j]);
            }
        }
        t[i] = temp;
        for (int j = 0; j < int(std::min(s[i].size(), t[i].size())); j++)
        {
            if (s[i][j] == t[i][j])
            {
                correct++;
            }
        }
    }
    int time;
    scanf("%d", &time);
    printf("%d\n", int(round(1.0 * correct / time * 60)));
    return 0;
}