#include <bits/stdc++.h>
using namespace std;

const int N = 100005;
int n, m, cnt;
vector<int> edges[N], T[N * 2]; // edges存储原图，T存储圆方树
int dfn[N], low[N], ti;
stack<int> st;
void Tarjan(int u)
{
    low[u] = dfn[u] = ++ti;
    st.push(u);
    for (int v : edges[u])
    {
        if (!dfn[v])
        {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
            if (low[v] == dfn[u]) // 表示找到一个以u为根的点双
            {
                ++cnt;
                int tmp;
                do // 将点双中除了 u 的点退栈，并在圆方树中连边
                {
                    tmp = st.top();
                    st.pop();
                    T[cnt].push_back(tmp);
                    T[tmp].push_back(cnt);
                } while (st.top() != u);
                // 注意 u 自身也要连边（但不退栈）
                T[cnt].push_back(u);
                T[u].push_back(cnt);
            }
        }
        else
            low[u] = min(low[u], dfn[v]); // 已访问的和 dfn 取 min
    }
}

int main()
{
    cin >> n >> m;
    cnt = n; // 点双 / 方点标号从 n 开始
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v); // 加双向边
        edges[v].push_back(u);
    }
    // 处理非连通图
    for (int u = 1; u <= n; ++u)
        if (!dfn[u])
            Tarjan(u), st.pop();
    // 注意到退出 Tarjan 时栈中还有一个元素即根，将其退栈
    cout << cnt << endl;
    return 0;
}