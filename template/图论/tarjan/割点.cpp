#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 2e5;
vector<int> edges[N + 1];
int dfn[N], low[N], ti;
vector<int> cut; // 存储所有割点编号
void tarjan(int u, bool root = true)
{
    int tot = 0;// 子节点数目
    low[u] = dfn[u] = ++ti;
    for (auto v : edges[u])
    {
        if (!dfn[v])
        {
            tarjan(v, false);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) // 统计满足low[v] >= dfn[u]的子节点数目
                tot++;
        }
        else
            low[u] = min(low[u], dfn[v]);
    }
    if (tot > root) // 如果是根，tot需要大于1；否则只需大于0
        cut.push_back(u);
}

signed main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i)
    {
        if (!dfn[i])
        {
            tarjan(i);
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        cout << i << " " << dfn[i] << " " << low[i] << endl;
    }
    for(auto i:cut)
        cout<<i<<" ";
}