#include <bits/stdc++.h>
using namespace std;
const int MAXV = 20000;
const int MAXE = 5;
const int INF = 1e9;
int capacity[MAXV][MAXE];
int flow[MAXV][MAXE];
vector<int> adj[MAXV];
int MaximumFlow(int source, int sink)
{
	int total_flow = 0;
	while (true)
	{
		vector<int> parent(MAXV, -1);
		vector<int> parentI(MAXV, -1);
		queue<int> q;
		parent[source] = source;
		q.push(source);
		while (!q.empty() && parent[sink] == -1)
		{
			int here = q.front();
			q.pop();
			for (int i = 0; i < adj[here].size(); i++)
			{
				int there = adj[here][i];
				if (capacity[here][i] - flow[here][i] > 0 && parent[there] == -1)
				{
					q.push(there);
					parent[there] = here;
					parentI[there] = i;
				}
			}
		}
		if (parent[sink] == -1)
			break;
		int amount = INF;
		for (int p = sink; p != source; p = parent[p])
			amount = min(capacity[parent[p]][parentI[p]] - flow[parent[p]][parentI[p]], amount);
		for (int p = sink; p != source; p = parent[p])
		{
			flow[parent[p]][parentI[p]] += amount;
			int i; for (i = 0; i < adj[p].size(); i++) if (adj[p][i] == parent[p]) break;
			flow[p][i] -= amount;
		}
		total_flow += amount;
	}
	return total_flow;
}
char c[MAXV >> 1][MAXV >> 1];
int di[4] = { -1, 1, 0, 0 }, dj[4] = { 0, 0, -1, 1 };
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n, m; cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		cin.ignore();
		for (int j = 0; j < m; j++)
		{
			cin >> c[i][j];
		}
	}
	int source, sink;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (c[i][j] == '#') continue;
			int currIn = 2 * (i * m + j);
			int currOut = 2 * (i * m + j) + 1;
			if (c[i][j] == 'K') source = currOut;
			if (c[i][j] == 'H') sink = currIn;
			capacity[currIn][adj[currIn].size()] = 1;
			adj[currIn].push_back(currOut);
			adj[currOut].push_back(currIn);
			for (int k = 0; k < 4; k++)
			{
				int ni = i + di[k], nj = j + dj[k];
				if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
				if (c[ni][nj] == '#') continue;
				int nextIn = 2 * (ni * m + nj);
				int nextOut = 2 * (ni * m + nj) + 1;
				capacity[currOut][adj[currOut].size()] = INF;
				adj[currOut].push_back(nextIn);
				adj[nextIn].push_back(currOut);
			}
		}
	}
	for (int next : adj[source])
	{
		if (next == sink)
		{
			cout << -1;
			return 0;
		}
	}
	cout << MaximumFlow(source, sink);
	return 0;
}