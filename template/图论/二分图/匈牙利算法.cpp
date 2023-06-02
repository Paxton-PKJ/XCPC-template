#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 505, M = 100010;
int n, m, k, a, b, ans;
struct edge//链式前向星存图
{
    int v, ne;
} e[M];
int h[N], idx;
int vis[N], match[N];//vis：女生v是否被匹配 match：女生v的男友

void add(int a, int b)
{
    e[++idx] = {b, h[a]};
    h[a] = idx;
}

bool dfs(int u)
{
    for (int i = h[u]; i; i = e[i].ne)//遍历男生可选的所有女生
    {
        int v = e[i].v; //妹子
        if (vis[v])
            continue;
        vis[v] = 1; //先标记这个女生为被选过
        if (!match[v] || dfs(match[v]))//如果女生没有对象，或者女生的男友可以选别的妹子
        {
            match[v] = u; //配成对
            return 1;
        }
    }
    return 0;
}

int main()
{
    cin >> n >> m >> k;
    for (int i = 0; i < k; i++)
        cin >> a >> b, add(a, b);
    for (int i = 1; i <= n; i++)
    {
        memset(vis, 0, sizeof vis);//每轮初始化所有妹子为可选
        if (dfs(i))
            ans++;//匹配增加
    }
    cout << ans;
    return 0;
}