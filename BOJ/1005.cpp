#include <bits/stdc++.h>
using namespace std;
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int t; cin >> t;
	while (t--)
	{
		int n, k; cin >> n >> k;
		vector<int> d(n), par(n);
		vector<vector<int>> adj(n);
		for (int i = 0; i < n; i++) cin >> d[i];
		for (int i = 0; i < k; i++)
		{
			int x, y; cin >> x >> y;
			x--, y--;
			adj[x].push_back(y);
			par[y]++;
		}
		int w; cin >> w;
		w--;
		queue<int> q;
		vector<int> dp(n, 0);
		for (int i = 0; i < n; i++)
			if (!par[i])
			{
				q.push(i);
			}
		while (par[w])
		{
			int curr = q.front(); q.pop();
			for (int next : adj[curr])
			{
				dp[next] = max(dp[next], dp[curr] + d[curr]);
				if (--par[next] == 0) q.push(next);
			}
		}
		cout << dp[w] + d[w] << '\n';
	}
	return 0;
}