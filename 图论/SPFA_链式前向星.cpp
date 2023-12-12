#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
const int inf = 0x3f3f3f3f;
const int maxn = 1e5 + 10;
struct edge
{
    int v, w;
};
vector<int> pre(maxn); // 记录路径
vector<edge> edges[maxn];
// dis 离原点的距离 cnt用于判断负环 vis标记
int dis[maxn], cnt[maxn];
bool vis[maxn];
bool spfa(int n, int s)
{
    queue<int> q;
    fill(dis, dis + maxn, inf);
    memset(vis, 0, sizeof vis);
    // 除了原点其他所有点更新为无穷，并且标记远点走过
    dis[s] = 0, vis[s] = 1, pre[s] = 0; // 初始化起点
    q.push(s);
    while (!q.empty())
    {
        int u = q.front();
        q.pop(), vis[u] = 0;
        for (auto i : edges[u]) // 遍历目标点位 更新关联的点
        {
            int v = i.v, w = i.w;
            if (dis[v] > dis[u] + w)
            { // 更新条件
                pre[v] = u;
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1; // 记录最短路经过的边数
                if (cnt[v] >= n)     // 在不经过负环的情况下，最短路至多经过 n - 1 条边
                    return false;    // 因此如果经过了多于 n 条边，一定说明经过了负环
                if (!vis[v])
                    q.push(v), vis[v] = 1; // 更新过的点不用入队更新，没更新过的点入队更新
            }
        }
    }
    return true;
}
signed main()
{
    IOS;
    int n, m, s;
    cin >> n >> m >> s;
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edges[u].push_back({v, w});
    }
    if (spfa(n, s))
    {
        for (int i = 1; i <= n; i++)
        {
            if (dis[i] > 1e9)
                cout << "INF ";
            else
                cout << dis[i] << " ";
        }
    }
    else
        cout << "存在负环" << endl;
    return 0;
}