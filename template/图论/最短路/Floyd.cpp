for (k = 1; k <= n; k++)
{
    for (x = 1; x <= n; x++)
    {
        for (y = 1; y <= n; y++)
        {
            f[x][y] = min(f[x][y], f[x][k] + f[k][y]);
        }
    }
}