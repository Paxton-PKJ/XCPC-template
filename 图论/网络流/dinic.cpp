#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
typedef long long ll;
const int inf = 0x3f3f3f3f;
struct dinic
{
    static const int MAXN = 1010;
    int n, s, t;
    int dep[MAXN], now[MAXN], vis[MAXN];
    struct Edge
    {
        ll from, to, val, flow; // from,to,val,flow分别表示边的起点，终点，容量，流量
        Edge(int from, int to, int val, int flow) : to(to), val(val), from(from), flow(flow){};
    };
    vector<Edge> edge;
    vector<int> mmp[MAXN]; //! 保存点i的所有出边编号

    void init(int _n, int _s, int _t)
    {
        n = _n;
        s = _s;
        t = _t;
        edge.clear();
        for (int i = 0; i <= n; i++)
        {
            mmp[i].clear();
            dep[i] = now[i] = vis[i] = 0;
        }
    }

    int add(int from, int to, ll val)
    {
        edge.push_back(Edge(from, to, val, 0));
        edge.push_back(Edge(to, from, 0, 0));
        int mm = edge.size();
        mmp[from].push_back(mm - 2);
        mmp[to].push_back(mm - 1);
        return mm - 2; // 返回正向边的编号
    }
    bool makelevel() // bfs构造分层图
    {
        memset(vis, 0, sizeof(vis));
        queue<int> q;
        q.push(s);  // 将源点加入队列
        dep[s] = 0; // 源点深度为1
        vis[s] = 1; // 源点已经被访问
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int i = 0; i < mmp[u].size(); i++) // 遍历点u的所有边
            {
                Edge &e = edge[mmp[u][i]];
                if (!vis[e.to] and e.flow < e.val) // 如果该边未被分层且仍具有容量
                {
                    vis[e.to] = 1;          // 该点已经被访问
                    dep[e.to] = dep[u] + 1; // 该点的深度为u的深度+1
                    q.push(e.to);
                }
            }
        }
        return vis[t];
    }
    ll dfs(int u, ll flow) // dfs寻找增广路,flow为当前路径上的最小流量,x为当前点,t为汇点
    {
        if (u == t or !flow) // 到达汇点，返回路径最小流量值，即最窄管道值
            return flow;
        ll outed = 0, tmp; // used用于记录当前点u向外流出的所有流量之和，也即使用了多少流到这个点的流量
        for (int &i = now[u]; i < mmp[u].size(); i++) // i使用引用，修改时会改变原值，即当前弧优化
        {
            Edge &e = edge[mmp[u][i]];
            if (dep[e.to] == dep[u] + 1 and (tmp = dfs(e.to, min(flow, e.val - e.flow))) > 0)
            // 如果该边具有容量且所连点位于下一层
            {
                // 一路搜索下去，得到路径最窄管道容量，在dfs进行到底层时才能得到该路径最大流量值
                e.flow += tmp;                   // 正向边流量增加
                edge[mmp[u][i] ^ 1].flow -= tmp; // 反向边流量减少
                outed += tmp;
                flow -= tmp; // 当前路径上的最小流量值减少
                if (!flow)
                    break; // 当前路径上的最小流量值为0，不必再继续搜索
            }
        }
        return outed; // 返回当前路径上的最小流量值
    }
    ll DINIC()
    {
        ll ans = 0;
        while (makelevel())
        {
            for (int i = 0; i <= n; i++)
                now[i] = 0;     // 重置当前弧
            ans += dfs(s, inf); // 每次寻找增广路，增加的流量
        }
        return ans;
    }
} dd;

signed main()
{
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    dd.init(n, s, t);
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        dd.add(u, v, w);
    }
    cout << dd.DINIC() << endl;
}