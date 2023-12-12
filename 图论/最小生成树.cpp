#include <algorithm>
#include <iostream>
#include <string.h>
using namespace std;
int fa[5005];

void init(int n) // 并查集初始化函数
{
    for (int i = 1; i <= n; ++i)
        fa[i] = i;
    return;
}

int find(int x) // 并查集找祖先函数
{
    return (x == fa[x] ? x : fa[x] = find(fa[x]));
}

struct line // 结构体
{
    int a, b, len;
} l[100000];

bool cmd(line a, line b) // 结构体排序
{
    return a.len < b.len;
}

int main()
{
    int n, m, sum = 0, num = 0; // sum边长度和   num已经使用的边数量
    while (cin >> n)            // n个点  m条边
    {
        if (n == 0)
            return 0;
        cin >> m;
        sum = 0, num = 0;
        memset(fa, 0, sizeof(fa));
        memset(l, 0, sizeof(l));

        for (int i = 1; i <= m; ++i)
        {
            cin >> l[i].a >> l[i].b >> l[i].len; // 输入边链接的两点和长度
        }
        sort(l + 1, l + 1 + m, cmd); // 将边按照长度由小到大排序
        init(n);                     // 初始化并查集
        for (int i = 1; i <= m; ++i) // 遍历边
        {
            int x = find(l[i].a), y = find(l[i].b); // 存储两条边的祖先
            if (x == y)                             // 两条边有共同祖先则会成环，不予考虑
                continue;
            sum += l[i].len;    // 加入长度总和
            fa[x] = y;          // 将x的父亲设置为y
            if (++num == n - 1) // 边的数量为点数量-1，最小生成树构建完成
            {
                cout << sum << endl;
                break;
            }
        }
        if (n == 1)
            cout << 0 << endl;
    }
    return 0;
}