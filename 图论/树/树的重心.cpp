#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 2e5 + 5;
int n;
vector<int> edges[N];
int Sonsize[N],       // 该点的子树总大小包括该点
    weight[N];        // 该点的重量，即最大子树大小
vector<int> centroid; // 存重心

void GetCentroid(int now, int fa)
{
    Sonsize[now] = 1;
    weight[now] = 0;
    for (auto v : edges[now])
    {
        if (v == fa)
            continue;
        GetCentroid(v, now);
        Sonsize[now] += Sonsize[v];
        weight[now] = max(weight[now], Sonsize[v]);
    }
    weight[now] = max(weight[now], n - Sonsize[now]);
    if (weight[now] <= n / 2)
    {
        centroid.emplace_back(now);
    }
}
signed main()
{
    int T;
    cin >> T;
    while (T--)
    {
        centroid.clear();
        for (int i = 0; i <= n; ++i)
        {
            edges[i].clear();
            Sonsize[i] = 0;
            weight[i] = 0;
        }
        cin >> n;
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            cin >> u >> v;
            edges[u].push_back(v);
            edges[v].push_back(u);
        }
        GetCentroid(1, 0);
        if (centroid.size() == 1)
        {
            cout << centroid[0] << " " << weight[centroid[0]] << endl;
        }
        else
        {
            int ans = 0;
            weight[centroid[0]] > weight[centroid[1]] ? ans = centroid[1] : ans = centroid[0];
            cout << ans << " " << weight[ans] << endl;
        }
    }
}