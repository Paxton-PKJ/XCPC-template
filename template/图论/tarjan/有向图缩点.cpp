#include <bits/stdc++.h>
#define N 10001

using namespace std;
#define all(x) (x).begin(), (x).end()
#define makeunique(x) sort(all(x)), (x).erase(unique(all(x)), (x).end())
vector<int> ve[N]; // 原图
stack<int> st;     // 栈
int n, m;
int dfn[N];         // 时间戳
int used[N];        // 是否访问过
int vis[N];         // 是否在栈中
int low[N];         // 能到达的最小时间戳
int belong[N];      // 染色
int sccnum = 0;     // 强连通分量的个数
int ti = 0;         // 时间戳
int ans = 0;        // 答案
vector<int> scc[N]; // 强连通分量
void tarjan(int u)
{
    dfn[u] = low[u] = ++ti;
    st.push(u);
    vis[u] = used[u] = true;
    for (auto v : ve[u])
    {
        if (!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (vis[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u])
    {
        sccnum++;
        int tmp;
        do
        {
            tmp = st.top();
            st.pop();
            belong[tmp] = sccnum;
            scc[sccnum].push_back(tmp);
            vis[tmp] = false;
        } while (tmp != u);
    }
}
int val[N];
int valn[N];
vector<int> ven[N];

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        cin >> val[i];
    }
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        ve[u].push_back(v);
    }
    for (int i = 1; i <= n; i++)
    {
        if (!used[i])
            tarjan(i);
    }
    for (int i = 1; i <= sccnum; ++i)
    {
        for (auto j : scc[i])
        {
            valn[i] += val[j];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (auto j : ve[i])
        {
            if (belong[i] != belong[j])
            {
                ven[belong[i]].push_back(belong[j]);
            }
        }
        makeunique(ven[belong[i]]);
    }
    return 0;
}