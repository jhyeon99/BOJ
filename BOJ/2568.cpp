#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
const int MAX = 100000;
using pii = pair<int, int>;
pii e[MAX];
int dp[MAX], idx[MAX];
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n; cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> e[i].first >> e[i].second;
	}
	sort(e, e + n);
	for (int i = 0; i < n; i++) dp[i] = INF;
	for (int i = 0; i < n; i++)
	{
		int x = lower_bound(dp, dp + n, e[i].second) - dp;
		dp[x] = e[i].second;
		idx[i] = x;
	}
	int m = lower_bound(dp, dp + n, INF) - dp - 1;
	int ans1 = n - (m + 1);
	cout << ans1 << '\n';
	bool ans2[MAX] = {};
	for (int i = n - 1, j = m; i >= 0; i--)
	{
		if (idx[i] == j)
		{
			ans2[i] = true;
			j--;
		}
	}
	for (int i = 0; i < n; i++)
		if (!ans2[i])
			cout << e[i].first << '\n';
	return 0;
}