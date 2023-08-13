#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 5e5+5;
vector<int> edges[N];
int dfn[N], low[N], ti;
vector<int> dcc[N]; // 存储所有点双连通分量
stack<int> st;
int num; // 存储点双连通分量的编号
void tarjan(int u, int root)
{
    low[u] = dfn[u] = ++ti;
    st.push(u);
    if (u == root and edges[u].size() == 0) // 特判根只有一个点且没有边的情况
    {
        ++num;
        dcc[num].push_back(u);
        return;
    }
    for (auto v : edges[u])
    {
        if (!dfn[v])
        {
            tarjan(v, false);
            low[u] = min(low[u], low[v]);
            // 如果v是u的子节点，且v的low值大于等于u的dfn值，说明u到v之间没有回边，即u和v之间是点双连通分量
            if (low[v] >= dfn[u])
            {
                ++num;
                int tmp;
                do
                {
                    tmp = st.top();
                    st.pop();
                    dcc[num].push_back(tmp);
                } while (tmp != v);// 将u到v之间的点都弹出，但不弹出u，由于点双连通分量割点性质
                dcc[num].push_back(u);
            }
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
        if (u == v)
            continue;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    for (int i = 1; i <= n; ++i)
    {
        if (!dfn[i])
        {
            tarjan(i, i);
        }
    }
    /* for (int i = 1; i <= n; ++i)
    {
        cout << i << " " << dfn[i] << " " << low[i] << endl;
    } */
    cout << num << endl;
    for (int i = 1; i <= num; ++i)
    {
        cout << dcc[i].size() << " ";
        for (auto j : dcc[i])
            cout << j << " ";
        cout << endl;
    }
}