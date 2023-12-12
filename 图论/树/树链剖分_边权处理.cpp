#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
#define mid(x, y) (((x) + (y)) >> 1)
#define ls(x) ((x) << 1)
#define rs(x) ((x) << 1 | 1)
#define len(x) (abs(t[(x)].r - t[(x)].l) + 1)
const int N = 1e5 + 10;
int cnt /* dfn计数 */, mod /* 取模 */, s;                  /* 根节点 */
int dep[N], fa[N], siz[N], son[N], top[N], dfn[N], rnk[N]; // 树剖相关数组
vector<pii> edges[N];
int val[N];

struct SegTree // 线段树维护路径信息
{
    // sum为路径和，maxx为区间最值，lazy为懒标记，pre为线段树叶子结点值
    struct Node
    {
        int l, r, sum, maxx, la, pre;
    } t[N * 4];
    void pushup(int p)
    {
        t[p].pre = (t[ls(p)].pre + t[rs(p)].pre) % mod;
        t[p].maxx = max(t[ls(p)].maxx, t[rs(p)].maxx);
    }
    void pushdown(int p)
    {
        if (t[p].la >= 1)
        {
            t[ls(p)].la += t[p].la;
            t[rs(p)].la += t[p].la;

            t[ls(p)].pre += t[p].la * len(ls(p));
            t[rs(p)].pre += t[p].la * len(rs(p));
            t[rs(p)].pre %= mod;
            t[ls(p)].pre %= mod;
            t[p].la = 0;
        }
    }
    void build(int p, int l, int r)
    {
        t[p].l = l, t[p].r = r;
        if (l == r)
        {
            t[p].pre = t[p].maxx = val[rnk[l]];
            return;
        }
        int mid = mid(l, r);
        build(ls(p), l, mid);
        build(rs(p), mid + 1, r);
        pushup(p);
    }
    void change(int p, int ql, int qr, int z)
    {
        if (ql <= t[p].l and t[p].r <= qr)
        {
            t[p].la += z;
            t[p].pre += z * len(p);
            return;
        }
        pushdown(p);
        int mid = mid(t[p].l, t[p].r);
        if (ql <= mid)
            change(ls(p), ql, qr, z);
        if (qr > mid)
            change(rs(p), ql, qr, z);
        pushup(p);
    }
    int query(int p, int ql, int qr)
    {
        if (ql <= t[p].l and t[p].r <= qr)
            return t[p].pre;
        pushdown(p);
        int mid = mid(t[p].l, t[p].r);
        int ans = 0;
        if (ql <= mid)
            ans += query(ls(p), ql, qr) % mod;
        if (qr > mid)
            ans += query(rs(p), ql, qr) % mod;
        return ans;
    }
};
SegTree st;

void dfs1(int now)
{
    // cout << now << endl;
    son[now] = -1;            // 重儿子初始化为 -1 表示没有重儿子
    siz[now] = 1;             // 节点 now 的子树大小初始化为 1
    for (auto i : edges[now]) // 遍历节点 now 的所有儿子
    {
        int v = i.first, w = i.second;
        if (!dep[v]) // 如果儿子节点还没有被遍历过
        {
            dep[v] = dep[now] + 1;                        // 更新儿子节点的深度+1
            fa[v] = now;                                  // 更新儿子节点的父节点为 now
            val[v] = w;                                   // 更新儿子节点的权值
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
    for (auto i : edges[now]) // 重儿子遍历完再遍历轻儿子
    {
        int v = i.first;
        if (v != son[now] && v != fa[now]) // 不是重儿子，也不是父亲，对轻儿子进行 DFS
            dfs2(v, v);
    }
} // 得到重链顶点top，dfs序dfn，dfs序对应的节点编号rnk

void addChain(int u, int v, int z)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        st.change(1, dfn[top[u]], dfn[u], z);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    st.change(1, dfn[u] + 1, dfn[v], z);
}

int queryChain(int u, int v)
{
    int sum = 0;
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        sum += st.query(1, dfn[top[u]], dfn[u]);
        sum %= mod;
        u = fa[top[u]];
    }
    if (dep[u] > dep[v])
        swap(u, v);
    sum += st.query(1, dfn[u] + 1, dfn[v]);
    return sum % mod;
}

signed main()
{
    int n, m;
    cin >> n >> m;
    mod = LONG_LONG_MAX;
    for (int i = 1; i < n; ++i)
    {
        int x, y, w = 0;
        cin >> x >> y;
        edges[x].push_back({y, w});
        edges[y].push_back({x, w});
    }
    s = 1;
    dep[s] = 1; // 根节点深度为 1
    dfs1(s);
    dfs2(s, s);
    st.build(1, 1, n);
    for (int i = 1; i <= m; ++i)
    {
        char t;
        int x, y;
        cin >> t;
        if (t == 'P')
            cin >> x >> y, addChain(x, y, 1);
        else if (t == 'Q')
            cin >> x >> y, cout << queryChain(x, y) % mod << endl;
    }
}