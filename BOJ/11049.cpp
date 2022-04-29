#include <bits/stdc++.h>
using namespace std;
const int INF = 2e9;
const int MAX = 500;
int r[MAX], c[MAX];
int dp[MAX][MAX];
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n; cin >> n;
	for (int i = 0; i < n; i++) cin >> r[i] >> c[i];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			dp[i][j] = i == j ? 0 : INF;
		}
	}
	for (int k = 1; k < n; k++)
	{
		for (int i = 0; i < n - k; i++)
		{
			for (int j = i; j < i + k; j++)
			{
				dp[i][i + k] = min(dp[i][i + k], dp[i][j] + dp[j + 1][i + k] + r[i] * c[j] * c[i + k]);
			}
		}
	}
	cout << dp[0][n - 1];
	return 0;
}