#include <bits/stdc++.h>
using namespace std;

class DominatorTree
{
  private:
    int n, m, tim = 0;
    vector<vector<vector<int>>> Edge = vector<vector<vector<int>>>(n + 10, vector<vector<int>>(3));
    // Edge[][0] 原图 1 反图 2 支配树
    vector<int> f, fa, mn, sdom, idom, dfn, rev, ans;

  public:
    DominatorTree(int n, int m) : n(n), m(m)
    {
        f.resize(n + 10);
        fa.resize(n + 10);
        mn.resize(n + 10);
        sdom.resize(n + 10);
        idom.resize(n + 10);
        dfn.resize(n + 10);
        rev.resize(n + 10);
        ans.resize(n + 10);
    }
    void addEdge(int u, int v)
    {
        Edge[u][0].push_back(v), Edge[v][1].push_back(u);
    }
    void dfs(int u)
    {
        rev[dfn[u] = ++tim] = u;
        for (auto v : Edge[u][0])
            if (!dfn[v])
                dfs(v), fa[v] = u;
    }
    int find(int x)
    {
        if (f[x] == x)
            return x;
        int res = find(f[x]);
        if (dfn[sdom[mn[f[x]]]] < dfn[sdom[mn[x]]])
            mn[x] = mn[f[x]];
        return f[x] = res;
    }
    void tarjan()
    {
        for (int i = 1; i <= n; ++i)
            f[i] = sdom[i] = mn[i] = i;
        for (int i = tim; i >= 2; --i)
        {
            int x = rev[i];
            for (auto v : Edge[x][1])
            { // 反图
                if (!dfn[v])
                    continue; // 不连通
                find(v);
                if (dfn[sdom[mn[v]]] < dfn[sdom[x]])
                    sdom[x] = sdom[mn[v]];
            }
            f[x] = fa[x], Edge[sdom[x]][2].push_back(x);
            for (auto v : Edge[x = fa[x]][2])
            {
                find(v);
                if (sdom[mn[v]] == x)
                    idom[v] = x;
                else
                    idom[v] = mn[v]; // 此时idom[v]可能没有找到
            }
            Edge[x][2].clear();
        }
        for (int i = 2; i <= tim; ++i)
        {
            int x = rev[i];
            if (idom[x] ^ sdom[x])
                idom[x] = idom[idom[x]];
            Edge[idom[x]][2].push_back(x);
        }
    }
    void handle()
    {
        for (int i = tim; i >= 2; i--)
            ans[idom[rev[i]]] += ++ans[rev[i]];
        ans[1]++;
    }
    void print_noendl()
    {
        for (int i = 1; i <= n; ++i)
            cout << ans[i] << " ";
    }
    void print()
    {
        print_noendl();
        cout << endl;
    }
};
void solve()
{
    int n, m;
    cin >> n >> m;
    DominatorTree dt(n, m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        cin >> u >> v;
        dt.addEdge(u, v);
    }
    dt.dfs(1);
    dt.tarjan();
    dt.handle();
    dt.print_noendl();
}
int main()
{
    setlocale(LC_ALL, ".utf-8");
    solve();
    return 0;
}