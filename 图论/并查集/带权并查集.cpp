#include <bits/stdc++.h>
using namespace std;

#define int long long
vector<int> fa(200005);// 存父节点
vector<int> d(200005); // 存权值，表示到根
int ans = 0;

void init(int x)
{
    for (int i = 1; i <= x; i++)
    {
        fa[i] = i;
        d[i] = 0;
    }
    return;
}

int find(int x)
{
    if (x != fa[x])
    {
        int rot = fa[x]; // 记录父节点编号
        fa[x] = find(fa[x]);
        d[x] += d[rot]; // 从根节点开始回溯，把权值累加
    }
    return fa[x];
}

void root(int x, int y, int v)
{
    int x_root = find(x); // 正常的并查集操作
    int y_root = find(y);
    if (x_root == y_root)
    {
        ans += (d[x] - d[y] != v); // 根节点相同，判断权值差是否与输入距离差相同
    }
    else
    {
        fa[x_root] = y_root;        // 将x的根节点接到y的根节点上去
        d[x_root] = v + d[y] - d[x]; // 修改权值
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
        ans = 0;
        init(n);
        for (int i = 1; i <= m; i++)
        {
            int x, y, v;
            cin >> x >> y >> v;
            root(x, y, v);
        }
        // cout << ans << endl;
        if (ans)
        {
            cout << "No" << endl;
        }
        else
        {
            cout << "Yes" << endl;
        }
    }
}