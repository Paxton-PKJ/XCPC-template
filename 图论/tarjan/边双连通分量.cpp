#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 500005;
vector<pair<int, int>> edges[N];// 存储边，pair的第一个元素是点的编号，第二个元素是边的编号
stack<int> st;
int dfn[N], low[N], ti;
vector<pair<int, int>> cut; // 存储所有割点编号
int dccnum;                 // 边双连通分量数量
int belong[N];              // 存储每个点属于的边双连通分量编号
vector<int> dcc[N];         // 存储所有边双连通分量
void tarjan(int u, int fa)
{
    low[u] = dfn[u] = ++ti;
    st.push(u);
    for (auto v : edges[u])
    {
        if (v.second == (fa ^ 1)) // 防止忽略重边导致错误
            continue;
        if (!dfn[v.first])
        {
            tarjan(v.first, v.second);
            low[u] = min(low[u], low[v.first]);
        }
        else
            low[u] = min(low[u], dfn[v.first]);
    }
    if (dfn[u] == low[u])
    {
        dccnum++;
        int tmp;
        do
        {
            tmp = st.top();
            st.pop();
            belong[tmp] = dccnum;
            dcc[dccnum].push_back(tmp);
        } while (tmp != u);
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
        edges[u].emplace_back(v, i << 1);
        edges[v].emplace_back(u, i << 1 | 1);
    }
    for (int i = 1; i <= n; ++i)
    {
        if (!dfn[i])
        {
            tarjan(i, 0);
        }
    }
    cout << dccnum << endl;
    for (int i = 1; i <= dccnum; ++i)
    {
        cout << dcc[i].size() << " ";
        for (auto j : dcc[i])
            cout << j << " ";
        cout << endl;
    }
}