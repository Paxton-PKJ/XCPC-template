#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 50005;
vector<int> edges[N + 1];
int dfn[N], low[N], ti;
vector<pair<int, int>> cut; // 存储所有割点编号
void tarjan(int u, int fa)
{
    low[u] = dfn[u] = ++ti;
    for (auto v : edges[u])
    {
        if (v == fa)
            continue;
        if (!dfn[v])
        {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) // 统计满足low[v] >= dfn[u]的子节点数目
                cut.emplace_back(u, v);
        }
        else
            low[u] = min(low[u], dfn[v]);
    }
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
            tarjan(i, 0);
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        cout << i << " " << dfn[i] << " " << low[i] << endl;
    }
    cout << cut.size() << endl;
}