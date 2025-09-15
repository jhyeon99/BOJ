#include <bits/stdc++.h>
using namespace std;
const int MAX = 501;
const int INF = 1e9;
int capacity[MAX][MAX], flow[MAX][MAX];
vector<int> adj[MAX];
int MaximumFlow(int source, int sink)
{
	int total_flow = 0;
	while (true)
	{
		vector<int> parent(MAX, -1);
		queue<int> q;
		parent[source] = source;
		q.push(source);
		while (!q.empty() && parent[sink] == -1)
		{
			int here = q.front();
			q.pop();
			for (int there = 0; there < MAX; there++)
			{
				if (capacity[here][there] - flow[here][there] > 0 && parent[there] == -1)
				{
					q.push(there);
					parent[there] = here;
				}
			}
		}
		if (parent[sink] == -1)
			break;
		int amount = INF;
		for (int p = sink; p != source; p = parent[p])
			amount = min(capacity[parent[p]][p] - flow[parent[p]][p], amount);
		for (int p = sink; p != source; p = parent[p])
		{
			flow[parent[p]][p] += amount;
			flow[p][parent[p]] -= amount;
		}
		total_flow += amount;
	}
	return total_flow;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n, m; cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int u, v, w; cin >> u >> v >> w;
		capacity[u][v] = capacity[v][u] += w;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	int source, sink; cin >> source >> sink;
	cout << MaximumFlow(source, sink);
	return 0;
}