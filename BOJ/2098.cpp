#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
const int MAX = 16;
int n;
int w[MAX][MAX];
int dp[MAX][1 << MAX];
int DFS(int curr, int vst)
{
	int& ret = dp[curr][vst];
	if (ret != INF) return ret;
	if (vst == (1 << n) - 1) return w[curr][0];
	for (int next = 1; next < n; next++)
	{
		if (vst & 1 << next || w[curr][next] == INF) continue;
		ret = min(ret, DFS(next, vst | 1 << next) + w[curr][next]);
	}
	return ret;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n;
	for (int u = 0; u < n; u++)
	{
		for (int v = 0; v < n; v++)
		{
			cin >> w[u][v];
			if (!w[u][v]) w[u][v] = INF;
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 1 << n; j++)
		{
			dp[i][j] = INF;
		}
	}
	dp[0][0] = 0;
	cout << DFS(0, 1);
	return 0;
}