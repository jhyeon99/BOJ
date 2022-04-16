#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
const int MAX = 100000;
const int STATE = 5;
int s[MAX];
int dp[MAX][STATE];
int W(int f, int t)
{
	if (f == t) return 1;
	else if (f == 0) return 2;
	else if ((f & 1) ^ (t & 1)) return 3;
	else return 4;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n = 0;
	while (true)
	{
		cin >> s[n];
		if (!s[n]) break;
		n++;
	}
	for (int i = 0; i < n; i++) fill_n(dp[i], STATE, INF);
	dp[0][0] = 2;
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < STATE; j++)
		{
			dp[i][j] = min(dp[i][j], dp[i - 1][j] + W(s[i - 1], s[i]));
			if (s[i - 1] != j) dp[i][s[i - 1]] = min(dp[i][s[i - 1]], dp[i - 1][j] + W(j, s[i]));
		}
	}
	int ans = INF;
	for (int i = 0; i < STATE; i++) ans = min(ans, dp[n - 1][i]);
	cout << ans;
	return 0;
}