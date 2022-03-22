#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100001;
const int MAXK = 17;
vector<int> adj[MAXN];
int depth[MAXN], parent[MAXN][MAXK];
void DFS(int curr)
{
	for (int next : adj[curr])
	{
		if (depth[next] == -1)
		{
			depth[next] = depth[curr] + 1;
			parent[next][0] = curr;
			DFS(next);
		}
	}
}
int LCA(int u, int v)
{
	if (depth[u] < depth[v])
	{
		swap(u, v);
	}
	int diff = depth[u] - depth[v];
	for (int k = 0; diff > 0; k++)
	{
		if (diff & 1) u = parent[u][k];
		diff >>= 1;
	}
	if (u != v)
	{
		for (int k = MAXK - 1; k >= 0; k--)
		{
			if (parent[u][k] != -1 && parent[u][k] != parent[v][k])
			{
				u = parent[u][k];
				v = parent[v][k];
			}
		}
		u = parent[u][0];
	}
	return u;
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
	memset(depth, -1, sizeof depth);
	memset(parent, -1, sizeof parent);
	depth[1] = 0;
	DFS(1);
	for (int k = 1; k < MAXK; k++)
	{
		for (int curr = 2; curr <= n; curr++)
		{
			if (parent[curr][k - 1] != -1)
			{
				parent[curr][k] = parent[parent[curr][k - 1]][k - 1];
			}
		}
	}
	int m; cin >> m;
	for (int i = 0; i < m; i++)
	{
		int u, v; cin >> u >> v;
		cout << LCA(u, v) << '\n';
	}
	return 0;
}