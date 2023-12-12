// 洛谷O2优化加速300ms
#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
typedef long long ll;
const ll inf = 0x3f3f3f3f;
struct mcmf
{
    static const int MAXN = 10100;
    int n, m, s, t;
    ll mincost = 0;
    bool vis[MAXN];
    int dis[MAXN];
    int incf[MAXN];
    int pre[MAXN];
    struct Edge
    {
        ll from, to, val, flow; // from,to,val,flow分别表示边的起点，终点，容量，流量
        ll cost;
        Edge(int from, int to, int val, int flow, ll cost) : to(to), val(val), from(from), flow(flow), cost(cost){};
    };
    vector<Edge> edge;
    vector<int> mmp[MAXN];

    void init(int _n, int _s, int _t)
    {
        n = _n;
        s = _s;
        t = _t;
        edge.clear();
        for (int i = 0; i <= n; i++)
        {
            mmp[i].clear();
            incf[i] = pre[i] = vis[i] = dis[i] = 0;
        }
    }
    int add(int from, int to, ll val, ll cost)
    {
        edge.push_back(Edge(from, to, val, 0, cost));
        edge.push_back(Edge(to, from, 0, 0, -cost));
        int mm = edge.size();
        mmp[from].push_back(mm - 2);
        mmp[to].push_back(mm - 1);
        return mm - 2;
    }
    bool spfa()
    {
        queue<int> q;
        memset(dis, 0x3f, sizeof(dis));
        memset(vis, 0, sizeof(vis));
        dis[s] = 0, vis[s] = 1, incf[s] = 1 << 30;
        q.push(s);
        while (!q.empty())
        {
            int u = q.front();
            q.pop(), vis[u] = 0;
            for (int i = 0; i < mmp[u].size(); ++i)
            {
                Edge &e = edge[mmp[u][i]];
                int v = e.to, cost = e.cost;
                if (dis[v] > dis[u] + cost and e.flow < e.val)
                {
                    dis[v] = dis[u] + cost;
                    incf[v] = min(1ll * incf[u], e.val);
                    pre[v] = mmp[u][i];
                    if (!vis[v])
                        q.push(v), vis[v] = 1;
                }
            }
        }
        return dis[t] != inf; // 依据题目具体要求修改此处
        // 当dis[t]为inf时，说明已经没有增广路了，费用流结束
        // 返回true则会进行下一次增广，返回false则费用流结束
    }
    void update()
    {
        int tmp = t;
        while (tmp != s)
        {
            int last = pre[tmp];
            edge[last].val -= incf[t];
            edge[last ^ 1].val += incf[t];
            tmp = edge[last].from;
        }
    }
    ll MCMF()
    {
        ll ans = 0;
        while (spfa()) // 能够在图中找到最小费用的增广路
        {
            update();                    // 更新网络流图
            ans += incf[t];              // 更新最大流
            mincost += incf[t] * dis[t]; // 更新最小费用
        }
        return ans;
    }
} mm;
signed main()
{
    IOS;
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    mm.init(n + 100, s, t);
    for (int i = 1; i <= m; i++)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        mm.add(a, b, c, d);
    }
    cout << mm.MCMF() << " " << mm.mincost;
}