#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;

int h[N], p[N], nxt[N], cnt;
int dep[N], fa[N], siz[N], son[N], top[N], dfn[N], rnk[N];

vector<int> edges[N];
void dfs1(int now)
{
    // cout << now << endl;
    son[now] = -1;            // 重儿子初始化为 -1 表示没有重儿子
    siz[now] = 1;             // 节点 now 的子树大小初始化为 1
    for (auto v : edges[now]) // 遍历节点 now 的所有儿子
    {
        if (!dep[v]) // 如果儿子节点还没有被遍历过
        {
            dep[v] = dep[now] + 1;                        // 更新儿子节点的深度+1
            fa[v] = now;                                  // 更新儿子节点的父节点为 now
            dfs1(v);                                      // 递归遍历儿子节点
            siz[now] += siz[v];                           // 更新节点 now 的子树大小
            if (son[now] == -1 || siz[v] > siz[son[now]]) // 由子树大小更新重儿子
                son[now] = v;
        }
    }
} // 得到重儿子son，父亲fa，深度dep，子树大小siz

void dfs2(int now, int t)
{
    // cout << now << endl;
    top[now] = t;       // 初始化重链顶为本身
    cnt++;              // dfs序++
    dfn[now] = cnt;     // 记录dfs序
    rnk[cnt] = now;     // 记录dfs序对应的节点编号
    if (son[now] == -1) // 如果没有重儿子，说明是叶子节点，直接返回
        return;
    dfs2(son[now], t);        // 优先对重儿子进行 DFS，保证同一条重链上的点 DFS 序连续
    for (auto v : edges[now]) // 重儿子遍历完再遍历轻儿子
    {
        if (v != son[now] && v != fa[now]) // 不是重儿子，也不是父亲，对轻儿子进行 DFS
            dfs2(v, v);
    }
} // 得到重链顶点top，dfs序dfn，dfs序对应的节点编号rnk

int lca(int u, int v)
{
    while (top[u] != top[v]) // 判断是否位于同一重链
    {
        if (dep[top[u]] > dep[top[v]]) // 不在同一重链，将深度较大的节点向上移动
            u = fa[top[u]];            // 移动至当前节点所在重链的顶点的父亲节点
        else
            v = fa[top[v]];
    }
    return dep[u] > dep[v] ? v : u; // 位于同一重链时，较小深度点为lca
}

int main()
{
    int n, m, s;
    cin >> n >> m >> s;
    for (int i = 1; i < n; ++i)
    {
        int x, y;
        cin >> x >> y;
        edges[x].push_back(y);
        edges[y].push_back(x);
    }
    dep[s] = 1; // 根节点深度为 1
    dfs1(s);
    dfs2(s, s);
    for (int i = 1; i <= m; ++i)
    {
        int a, b;
        cin >> a >> b;
        cout << lca(a, b) << endl;
    }
}