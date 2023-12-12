#include <cstring>
#include <iostream>
#include <queue>
#include <utility>
using namespace std;
struct Edge
{
    int to, nexty, val; // to去向
} edge[200005];
int dis[100005];  //起点到第i个点的最短距离
bool vis[100005]; //点位标记
int head[200005];
int cnt = 0, n, m, s;
priority_queue<pair<int, int>> q; //优先队列，大顶堆，第一个元素
//使用pair作为优先队列的元素时，先比较第一个元素，第一个相等比较第二个
void dij()
{
    memset(dis, 0x3f, sizeof(dis)); //距离初始化为无穷大
    dis[s] = 0;                     //起点到自己的最短路径就是0
    q.push(make_pair(0, s)); // make_pair()将距离和点编号组合生成一个pair对象，并压入优先队列
    while (q.size())         // q不为空执行循环
    {
        int x = q.top().second; //将x赋值为当前出发点编号
        q.pop();                //弹出
        if (vis[x])             //该点已被计算则跳过
            continue;
        vis[x] = true;
        for (int i = head[x]; i != 0; i = edge[i].nexty) //循环遍历该点的下一步点
        {
            if (dis[edge[i].to] > dis[x] + edge[i].val) //该点没有被走过，dis[edge[i].to]为无穷大，必然大于后者
            {
                dis[edge[i].to] = dis[x] + edge[i].val;          //将该点的dis赋值
                q.push(make_pair(-dis[edge[i].to], edge[i].to)); //对dis取反将小根堆改写为大根堆
            } //大根堆大数在前，例如-1，-2，-5，变相将距离较小的点排在队列头
        }
    }
}

inline void add(int a, int b, int c) //链式前向星
{
    edge[++cnt].to = b;
    edge[cnt].val = c;
    edge[cnt].nexty = head[a];
    head[a] = cnt;
}

int main()
{
    cin >> n >> m >> s; // n 个点，m 条有向边的带非负权图，从s出发
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w; //从u到v有一条权值为w的有向边
        add(u, v, w);       //添加边
    }
    dij();
    for (int i = 1; i <= n; i++)
        cout << dis[i] << " ";
    return 0;
}