#include <algorithm>
#include <cstdio>
int s, a, b, x;
int main()
{
    scanf("%d%d%d%d", &s, &a, &b, &x);
    printf("%d\n", s * a * (x / (a + b)) + s * std::min(a, x % (a + b)));
    return 0;
}