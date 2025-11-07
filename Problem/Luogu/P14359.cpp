#include <cstdio>
#include <map>
int n, k;
int answer;
std::map<int, bool> map;
int main()
{
    scanf("%d%d", &n, &k);
    int cur = 0;
    for (int i = 1; i <= n; i++)
    {
        int x;
        scanf("%d", &x);
        cur ^= x;
        if (map[k ^ cur] || k == cur)
        {
            cur = 0;
            answer++;
            map.clear();
        }
        map[cur] = true;
    }
    printf("%d\n", answer);
    return 0;
}