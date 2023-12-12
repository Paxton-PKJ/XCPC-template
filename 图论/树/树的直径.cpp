// https://rinfly.com/p/loj-10159.html
#include <bits/stdc++.h>
using namespace std;
const int N = 200000 + 10;
int n, d = 0; // n个点，d为直径长度
vector<int> edges[N];
//---------------------------树形dp---------------------------
namespace tree_dp
{
int d1[N], d2[N]; // 向下最大深度与次大深度
void dfs(int u, int fa)
{

    // 一个点的最大深度+次大深度=该点的最大直径
    d1[u] = d2[u] = 0; // d1[u]表示以u为根的子树的最大深度，d2[u]表示以u为根的子树的次大深度
    for (int v : edges[u])
    {
        if (v == fa)
            continue;
        dfs(v, u);
        int t = d1[v] + 1; // +1表示由子树v的最大深度推得的u的深度
        if (t > d1[u])     // v子树得到的深度比当前记录最大的大，更新
        {
            d2[u] = d1[u], d1[u] = t;
        }
        else if (t > d2[u]) // 比次大的大，更新
        {
            d2[u] = t;
        }
    }
    d = max(d, d1[u] + d2[u]); // 更新最大直径
}

set<int> PointSet; // 直径的所有端点集合
int up[N];         // 点x向上最大深度
void ProcessPath(int u, int fa)//计算树中所有点的向上最大深度，便于标记所有直径点
{
    int siz = 0; // 记录u的子树中，与u距离最大的点的个数
    for (auto v : edges[u])
    {
        if (v == fa)
            continue;
        if (d1[v] + 1 == d1[u])
            siz++;
        if (siz > 1)
            break;
    }
    for (auto v : edges[u])
    {
        if (v == fa)
            continue;
        if (siz > 1 || d1[v] + 1 != d1[u])
            up[v] = max(up[u], d1[u]) + 1;
        else //
            up[v] = max(up[u], d2[u]) + 1;
        ProcessPath(v, u);
    }
}
void solve()
{
    dfs(1, 0);
    ProcessPath(1, 0);
    for (int i = 1; i <= n; ++i)
    {
        if (d1[i] + max(up[i], d2[i]) < d)
            continue;
        PointSet.insert(i); // 直径的所有途径点集合
    }
    cout << d << endl;
}
} // namespace tree_dp
//---------------------------两次dfs---------------------------
namespace twice_dfs
{
bool vis[N];
int dis[N];
int fa[N];
void dfs(int now, int f, int length, int mod)
{
    dis[now] = length;
    fa[now] = f;
    if (length >= d)
    {
        d = length;
        lenpoint[mod] = now;
    }
    for (auto i : edges[now])
    {
        int v = i.first, w = i.second;
        if (v == f)
            continue;
        dfs(v, now, length + w, mod);
    }
}
void find()
{
    dfs(1, 0, 0, 0); // 从1出发dfs一次
    memset(dis, 0, sizeof dis);
    dfs(lenpoint[0], 0, 0, 1); // 从直径端点出发dfs一次
}

void solve()
{
    cout << find() << endl;
}
} // namespace twice_dfs

int main()
{
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v), edges[v].push_back(u);
    }
    twice_dfs::solve();
    // tree_dp::solve();
    return 0;
}