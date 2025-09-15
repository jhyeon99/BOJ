#include <bits/stdc++.h>
using namespace std;
const int MAX = 400;
const int INF = 1e9;
int capacity[MAX][MAX];
int flow[MAX][MAX];
inline int In(int i)
{
	return i << 1;
}
inline int Out(int i)
{
	return i << 1 | 1;
}
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
	int source, sink; cin >> source >> sink;
	source--, sink--;
	for (int i = 0; i < n; i++)
	{
		int w; cin >> w;
		capacity[In(i)][Out(i)] = w;
	}
	for (int i = 0; i < m; i++)
	{
		int u, v; cin >> u >> v;
		u--; v--;
		capacity[Out(u)][In(v)] = capacity[Out(v)][In(u)] = INF;
	}
	MaximumFlow(In(source), Out(sink));
	vector<int> parent(MAX, -1);
	queue<int> q;
	parent[In(source)] = In(source);
	q.push(In(source));
	while (q.size())
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
	for (int i = 0; i < 2 * n; i += 2)
	{
		if (parent[i] != -1 && parent[i + 1] == -1)
		{
			cout << (i >> 1) + 1 << ' ';
		}
	}
	return 0;
}