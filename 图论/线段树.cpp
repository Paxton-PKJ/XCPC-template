#include <cstdio>
#include <iostream>
using namespace std;
struct tt
{
    int l, r;          // l，r为这个点统率的区间长度
    long long la, pre; // la代表这个点的lazy值，pre代表这个点的存储的值
} t[400005];

int a[100005]; // 存储最一开始的数字

void build(int p, int l, int r) // 建树，点p的统率长度为l-r
{
    t[p].l = l, t[p].r = r; // 存储该点统率长度左端点和右端点
    if (l == r)             // 叶子结点，直接赋值
    {
        t[p].pre = a[r];
        return;
    }
    int mid = (l + r) >> 1;                       // 取中值
    build(p << 1, l, mid);                        // 递归建左树
    build(p << 1 | 1, mid + 1, r);                // 递归建右树  p << 1 | 1  p乘2+1
    t[p].pre = t[p << 1].pre + t[p << 1 | 1].pre; // 当前点的值就等于左子树的值+右子树的值
}

int len(int a)
{
    return t[a].r - t[a].l + 1;
} // 返回一个点的区间长度
void lazy(int p)
{                     // 下传懒标记，某个节点打上懒标记说明它表示的区间值都要更改
    if (t[p].la >= 1) // 点p存在懒标记
    {
        t[p << 1].pre += t[p].la * (len(p << 1)); // 点p左右节点的值加上懒标记值*左右节点的长度
        t[p << 1 | 1].pre += t[p].la * (len(p << 1 | 1));
        t[p << 1].la += t[p].la; // 下传懒标记，即懒标记合并
        t[p << 1 | 1].la += t[p].la;
        t[p].la = 0; // 清除当前懒标记
    }
}

void change(int p, int x, int y, int z) // p点，xy为区间，z为值  [x,y]区间更改z值
{                                       // 原理为重复递归直到x-y超过点表示区间，标记lazy
    if (t[p].l >= x && t[p].r <= y)     // 如果[x,y]完全覆盖该点表示区间
    { // 将该点的值修改为更改值乘该点区间长度，也就是表示的所有区间点都要加上该值
        t[p].pre += (long long)z * (len(p));
        t[p].la += z; // 该点打上lazy值
        return;
    }
    lazy(p); // 如果不是所有点都要更改则需要下传懒标记，若不存在懒标记，忽略此步
    int mid = (t[p].l + t[p].r) >> 1; // 求出该点区间中值
    // 判断修改区间位置
    if (x <= mid)
        change(p << 1, x, y, z);
    if (y > mid)
        change(p << 1 | 1, x, y, z);
    t[p].pre = t[p << 1].pre + t[p << 1 | 1].pre;
    // 找到了表示区间全部都要被修改的点，则将该点的父结点的值修改
}

long long query(int p, int x, int y) // 查询某区间上的和
{                                    // 和区间修改原理差不多
    if (x <= t[p].l && y >= t[p].r)  // 涵盖了整个区间的话直接返回当前节点值
        return t[p].pre;
    lazy(p); // 因为并不是所有区间都要被查询，也就是需要使用子节点，存在懒标记，进行下传
    int mid = (t[p].l + t[p].r) >> 1;
    long long ans = 0;
    if (x <= mid)
        ans += query(p << 1, x, y);
    if (y > mid)
        ans += query(p << 1 | 1, x, y);
    return ans;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    build(1, 1, n); // 建树
    //
    while (m--)
    {
        int d, x, y, k;
        scanf("%d", &d);
        if (d == 1)
        {
            scanf("%d%d%d", &x, &y, &k);
            change(1, x, y, k);
            // for(int i=1;i<=4*n;i++) cout<<i<<":"<<t[i].l<<" "<<t[i].r<<" "<<t[i].pre<<" "<<endl;
        }
        else
        {
            scanf("%d%d", &x, &y);
            cout << query(1, x, y) << endl;
        }
    }
}
