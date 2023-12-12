#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf = INT_MAX;
struct isap
{
    int n, m, s, t; // n个点 m条边 s源点 t汇点
    int cnt = 1;
    vector<int> dep, gap, head, now;
    // depi的深度 gap深度为i的点的数量 head第i个点属于第几条边 now表示i点的当前弧，定义见笔记
    struct Edge
    {
        ll to, next, val, from; // v边的终点 next边的下一条边 val边的残量
        Edge(int from = 0, int to = 0, int next = 0, int val = 0) : to(to), next(next), val(val), from(from){};
    };
    vector<Edge> edge;

    isap(int n, int m, int s, int t) : n(n), m(m), s(s), t(t), head(n), dep(n), gap(n), now(n), edge(m){};
    void add(int a, int b, ll c)
    {
        edge[++cnt] = Edge(a, b, head[a], c);
        head[a] = cnt;
        edge[++cnt] = Edge(b, a, head[b], 0);
        head[b] = cnt;
    }

    void bfs() // 倒着搜
    {
        fill(dep.begin(), dep.end(), -1); // 把深度变为-1(0会导致gap崩坏)
        fill(gap.begin(), gap.end(), 0);
        dep[t] = 0; // 汇点深度为0
        gap[0] = 1; // 深度为0的点有1个
        queue<int> q;
        q.push(t); // t点入栈
        while (!q.empty())
        {
            int now = q.front();
            q.pop();
            for (int i = head[now]; i; i = edge[i].next)
            // head[u]:u点所在的边,node[i].next:u点所在的边的下一个点，就这样遍历下去
            {
                int v = edge[i].to;
                if (dep[v] != -1)
                    continue; // v点已被遍历
                q.push(v);
                dep[v] = dep[now] + 1; // v点的深度比u点大1
                gap[dep[v]]++;
            } // 直到所有点都被遍历过
        }
        return;
    } // 从t到s跑一遍bfs，标记深度
    ll maxflow;
    int dfs(int u, int flow = inf)
    {
        if (u == t) // 到达汇点，返回路径最大流量值
        {
            maxflow += flow;
            return flow;
        }
        int used = 0; // used用于记录当前点u流出的所有流量之和
        for (int i = now[u]; i; i = edge[i].next)
        {
            now[u] = i; // 更新当前弧
            int d = edge[i].to;
            if (edge[i].val and dep[d] + 1 == dep[u]) // 如果这条边的残量大于0,且没有断层
            {
                ll tmp = dfs(d, min(edge[i].val, (ll)flow - used)); //
                edge[i].val -= tmp;
                edge[i ^ 1].val += tmp;
                used += tmp;
                if (used == flow)
                    return used;
            }
        }
        // 如果已经到了这里，说明该点出去的所有点都已经流过了
        // 并且从前面点传过来的流量还有剩余
        // 则此时，要对该点更改dep
        // 使得该点与该点出去的点分隔开
        // 使得前面点流出的流量不会经过该点，从而可以寻找新的可行流
        --gap[dep[u]]; // 该层的点少了一个
        if (gap[dep[u]] == 0)
            dep[s] = n + 1; // 出现断层，无法到达t了,dep[s] = n+1,直接置为结束条件
        dep[u]++;           // 层++
        gap[dep[u]]++;      // 层数对应个数++
        return used;        // 返回本次增广的流量
    }
    ll ISAP()
    {
        maxflow = 0;
        bfs();
        while (dep[s] < n)
            now = head,
            dfs(s, inf); // 每次dfs,s的层数会加1,如果一直没有出现断层,最多跑n-dep(刚bfs完时s的深度)条增广路共有n个点
        return maxflow;
    }
};

void solve()
{
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    isap ii(4 * n, 5 * m, s, t);
    int u, v, w;
    for (int i = 1; i <= m; i++)
    {
        cin >> u >> v >> w;
        ii.add(u, v, w);
    }
    cout << ii.ISAP() << endl;
}
int main()
{
    solve();
    return 0;
}