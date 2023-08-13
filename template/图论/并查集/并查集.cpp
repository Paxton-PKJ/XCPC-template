#include <bits/stdc++.h>
using namespace std;

#define int long long
vector<int> fa(200005);// 存父节点
int ans = 0;

void init(int x)
{
    for (int i = 1; i <= x; i++)
    {
        fa[i] = i;
    }
    return;
}

int find(int x)
{
    if (x != fa[x])
    {
        int rot = fa[x]; // 记录父节点编号
        fa[x] = find(fa[x]);
    }
    return fa[x];
}

void root(int x, int y, int v)
{
    int x_root = find(x); // 正常的并查集操作
    int y_root = find(y);
    if (x_root != y_root)
    {
        fa[x_root] = y_root;        // 将x的根节点接到y的根节点上去
    }
}

signed main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        init(n);
        for (int i = 1; i <= m; i++)
        {
            int x, y;
            cin >> x >> y;
            root(x, y);
        }
    }
}