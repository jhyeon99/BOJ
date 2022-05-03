#include <bits/stdc++.h>
using namespace std;
const int INF = 2e9;
const int MAX = 1000;
const int COLOR = 3;
int cost[MAX][COLOR];
int dp[MAX][COLOR][COLOR];
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n; cin >> n;
	for (int i = 0; i < n; i++) cin >> cost[i][0] >> cost[i][1] >> cost[i][2];
	for (int i = 0; i < n; i++) for (int j = 0; j < COLOR; j++) for (int k = 0; k < COLOR; k++) dp[i][j][k] = INF;
	for (int k = 0; k < COLOR; k++) dp[0][k][k] = cost[0][k];
	for (int i = 1; i < n; i++)
		for (int j = 0; j < COLOR; j++)
			for (int k = 0; k < COLOR; k++)
				for (int l = 0; l < COLOR; l++)
					if (k != l)
						dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][l] + cost[i][k]);
	int ans = INF;
	for (int j = 0; j < COLOR; j++)
		for (int k = 0; k < COLOR; k++)
			if (j != k)
				ans = min(ans, dp[n - 1][j][k]);
	cout << ans;
	return 0;
}