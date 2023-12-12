/* 
https://www.luogu.com.cn/problem/CF685B
CF685B Kay and Snowflake
树的重心
O(n)
 */
#include <bits/stdc++.h>
using namespace std;

const int N = 327680;
int n, q;
int siz[N], h_son[N], father[N]; // f[i]是以i为根的子树的节点数；h_son[i]是i的重儿子。
int centroid[N];
vector<int> edges[N];

void dfs(int now, int fa) // 求以now为根的子树的重心
{
    siz[now] = 1, father[now] = fa, centroid[now] = now; // 叶子节点的重心是它自己
    for (auto v : edges[now])
    {
        dfs(v, now);
        siz[now] += siz[v];           // 更新节点数
        if (siz[v] > siz[h_son[now]]) // 更新重儿子信息
            h_son[now] = v;
    }
    if (!h_son[now]) // 不存在重儿子，叶子节点
        return;
    int cent = centroid[h_son[now]]; // 取出重儿子子树重心
    while (cent != now)              // 从重儿子子树重心开始向上找重心
    {
        if (siz[now] - siz[cent] <= (siz[now] >> 1) and siz[h_son[cent]] <= (siz[now] >> 1))
        { // 如果以cent为根的子树的节点数不超过总节点数的一半，且cent的重儿子的节点数不超过总节点数的一半
            centroid[now] = cent;
            break;
        }
        cent = father[cent];// 否则继续向上找重心
    }// 重心一定在根的重链上，故从重儿子的重心向上向根方向寻找重心一定正确
}

int main()
{
    cin >> n >> q;
    for (int i = 2; i <= n; ++i)
    {
        int tmp;
        cin >> tmp;
        edges[tmp].push_back(i);
    }
    dfs(1, 0);
    for (int i = 1; i <= q; ++i)
    {
        int tmp;
        cin >> tmp;
        cout << centroid[tmp] << endl;
    }
    return 0;
}