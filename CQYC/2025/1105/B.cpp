#include <cstdio>
#include <cstdlib>
#include <vector>
constexpr int MaxN = 1e5 + 5;
int n;
int have[MaxN][3];
long long answer;
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= 2 * n; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        if (!(1 <= y && y <= 2))
        {
            if (y < 1)
            {
                answer += 1 - y;
                y = 1;
            }
            if (y > 2)
            {
                answer += y - 2;
                y = 2;
            }
        }
        if (!(1 <= x && x <= n))
        {
            if (x < 1)
            {
                answer += 1 - x;
                x = 1;
            }
            if (x > n)
            {
                answer += x - n;
                x = n;
            }
        }
        have[x][y]++;
    }
    std::vector<int> wait[3];
    std::vector<int> more[3];
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= have[i][1]; j++)
        {
            more[1].push_back(i);
        }
        for (int j = 1; j <= have[i][2]; j++)
        {
            more[2].push_back(i);
        }
        wait[1].push_back(i);
        wait[2].push_back(i);
        for (; !wait[1].empty() && !more[1].empty();)
        {
            answer += abs(wait[1].back() - more[1].back());
            wait[1].pop_back();
            more[1].pop_back();
        }
        for (; !wait[2].empty() && !more[2].empty();)
        {
            answer += abs(wait[2].back() - more[2].back());
            wait[2].pop_back();
            more[2].pop_back();
        }
        for (; !wait[1].empty() && !more[2].empty();)
        {
            answer += abs(wait[1].back() - more[2].back()) + 1;
            wait[1].pop_back();
            more[2].pop_back();
        }
        for (; !wait[2].empty() && !more[1].empty();)
        {
            answer += abs(wait[2].back() - more[1].back()) + 1;
            wait[2].pop_back();
            more[1].pop_back();
        }
    }
    printf("%lld\n", answer);
    return 0;
}