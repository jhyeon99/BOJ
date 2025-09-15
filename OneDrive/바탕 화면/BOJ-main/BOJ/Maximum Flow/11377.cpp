#include <bits/stdc++.h>
using namespace std;
const int MAX = 2003;
const int INF = 1e9;
vector<int> adj[MAX];
int capacity[MAX][MAX], flow[MAX][MAX];
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
			for (int there : adj[here])
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
void AddEdge(int u, int v, int w)
{
	adj[u].push_back(v);
	adj[v].push_back(u);
	capacity[u][v] = w;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n, m, k; cin >> n >> m >> k;
	int source = 0, bridge = 1, sink = n + m + 2;
	AddEdge(source, bridge, k);
	for (int i = 2; i < n + 2; i++)
	{
		AddEdge(source, i, 1);
		AddEdge(bridge, i, 1);
		int t; cin >> t;
		while (t--)
		{
			int j; cin >> j;
			j += n + 1;
			AddEdge(i, j, 1);
		}
	}
	for (int i = n + 2; i < n + m + 2; i++)
	{
		AddEdge(i, sink, 1);
	}
	cout << MaximumFlow(source, sink);
	return 0;
}