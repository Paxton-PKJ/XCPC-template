// deg是入度，在存图的时候需要录入数据
// A是排序后的数组
int deg[MAXN], A[MAXN];
bool toposort(int n)
{
    int cnt = 0;
    queue<int> q;//队列用于储存当前图中所有入度为0的节点
    for (int i = 1; i <= n; ++i)//遍历寻找入度为0的节点
        if (deg[i] == 0)
            q.push(i);//压入队列
    while (!q.empty())//存在入度为0的节点
    {
        int t = q.front();
        q.pop();//保存后将其弹出
        A[cnt++] = t;//逐个保存节点顺序
        for (auto to : edges[t])
        {
            deg[to]--;
            if (deg[to] == 0) // 删除节点后出现了新的入度为0的点
                q.push(to);
        }
    }
    return cnt == n;
}