#include <bits/stdc++.h>
using namespace std;
const int MAX = 1000001;
vector<int> adj[MAX];
bool vst[MAX];
int dp[MAX][2];
void DFS(int curr)
{
	vst[curr] = true;
	dp[curr][0] = 0;
	dp[curr][1] = 1;
	for (int next : adj[curr])
	{
		if (vst[next]) continue;
		DFS(next);
		dp[curr][0] += dp[next][1];
		dp[curr][1] += min(dp[next][0], dp[next][1]);
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n; cin >> n;
	for (int i = 0; i < n - 1; i++)
	{
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	DFS(1);
	cout << min(dp[1][0], dp[1][1]);
	return 0;
}