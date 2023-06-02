#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define LL long long
#define N 510
#define INF 1e12
int n, m;
int match[N];     //右点匹配了哪个左点
int va[N], vb[N]; //标记是否在交替路中
LL la[N], lb[N];  //左顶标,右顶标
LL w[N][N], d[N]; //维护更新的delta值

bool dfs(int x)
{
    va[x] = 1; // x在交替路中
    for (int y = 1; y <= n; y++)//遍历所有右点
    {
        if (!vb[y])//右点不在交替路中
        {
            if (la[x] + lb[y] - w[x][y] == 0)//且左右顶标相加等于该边权
            {              //相等子图
                vb[y] = 1; // y在交替路中
                if (!match[y] || dfs(match[y]))//右点未被匹配或者右点对应的左点还可匹配其他右点
                {
                    match[y] = x; //配对
                    return 1;
                }
            }
            else //不是相等子图则记录最小的d[y]
                d[y] = min(d[y], la[x] + lb[y] - w[x][y]);
        }
    }
    return 0;
}

LL KM()
{
    //左顶标取i的出边的最大边权
    for (int i = 1; i <= n; i++)//初始化所有左顶标为负无穷
        la[i] = -INF;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            la[i] = max(la[i], w[i][j]);//取左顶标为相连边的边权最大值
    for (int i = 1; i <= n; i++)//初始化右顶标为0
        lb[i] = 0;
    for (int i = 1; i <= n; i++)//遍历所有左点
    {
        while (true)
        { //直到左点i找到匹配
            fill(va + 1, va + n + 1, 0);//初始化左右交替路标记为0
            fill(vb + 1, vb + n + 1, 0);
            fill(d + 1, d + n + 1, INF);//初始化delta值为正无穷
            if (dfs(i))//在左点找到匹配之前不会退出循环
                break;
            LL delta = INF;
            for (int j = 1; j <= n; j++)
                if (!vb[j])
                    delta = min(delta, d[j]);//找到每个左点delta值的最小值
            for (int j = 1; j <= n; j++)//依据delta最小值将已经在交替路中的顶点顶标左减右加
            { //修改顶标
                if (va[j])
                    la[j] -= delta;
                if (vb[j])
                    lb[j] += delta;
            }
        }
    }
    LL res = 0;
    for (int i = 1; i <= n; i++)
        res += w[match[i]][i];//将边权相加返回
    return res;
}
int main()
{
    scanf("%d%d", &n, &m);//n个左点  m条边
    for (int i = 1; i <= n; i++)//初始化所有边权为负无穷
        for (int j = 1; j <= n; j++)
            w[i][j] = -INF;
    for (int i = 1; i <= m; i++)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        w[x][y] = z;//从左点x到右点y有一条边权为z的边
    }
    printf("%lld\n", KM());//输出最大匹配边权和
    for (int i = 1; i <= n; i++)
        printf("%d ", match[i]);//输出每个左点匹配到的右点
    return 0;
}