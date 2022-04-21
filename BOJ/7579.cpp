#include <bits/stdc++.h>
using namespace std;
const int INF = 2e9;
const int MAX = 101;
int mem[MAX], cost[MAX];
int dp[MAX][MAX * MAX];
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n, m; cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> mem[i];
	for (int i = 1; i <= n; i++) cin >> cost[i];
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j <= 100 * n; j++)
		{
			dp[i][j] = dp[i - 1][j];
			if (i > 0 && j >= cost[i])
			{
				dp[i][j] = max(dp[i][j], dp[i - 1][j - cost[i]] + mem[i]);
			}
		}
	}
	for (int i = 0; i <= 100 * n; i++)
	{
		if (dp[n][i] >= m)
		{
			cout << i;
			break;
		}
	}
	return 0;
}