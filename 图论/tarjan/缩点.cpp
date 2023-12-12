vector<int> ve[10005]; //原图
int val[10005];        //原图节点值
stack<int> st;         //栈
bool vis[10005];       //栈弹出用
int dfn[10005];        //强分过程用
int low[10005];        //强分过程用
int belong[10005];     //点所在的强分编号
int num;               //强连通分量数量
int ti = 0;
int ans = 0;

void tarjan(int x)
{
    st.push(x);
    vis[x] = 1;
    dfn[x] = low[x] = ++ti;
    for (auto i : ve[x]) //对x能够抵达的点遍历
    {
        if (dfn[i] == 0) //该点没有被遍历过
        {
            tarjan(i); //进入递归，并输入栈
            low[x] = min(low[x], low[i]);
        }
        else if (vis[i]) //存在栈中，即之前已经走过该点，现在回到该点
        {
            low[x] = min(low[x], low[i]); //说明点i存在有一个回路到达点x，修改low值
        }
    }
    if (dfn[x] == low[x])
    {
		num++;
		int temp;
		do
		{
			temp = st.top();
			belong[temp] = num;
			st.pop();
		} while (temp!=x);
    }
}