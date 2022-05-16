#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int MAX = 10001;
vector<pii> adj[MAX], invadj[MAX];
int par[MAX];
int dist[MAX];
bool vst[MAX];
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n, m; cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int u, v, w; cin >> u >> v >> w;
		adj[u].push_back(pii(w, v));
		par[v]++;
		invadj[v].push_back(pii(w, u));
	}
	int s, e; cin >> s >> e;
	queue<int> q1;
	q1.push(s);
	while (q1.size())
	{
		int curr = q1.front();
		q1.pop();
		for (pii p : adj[curr])
		{
			int next = p.second;
			dist[next] = max(dist[next], dist[curr] + p.first);
			if (!--par[next])
			{
				q1.push(next);
			}
		}
	}
	int ans1 = 0, ans2 = 0;
	for (int i = 1; i <= n; i++) ans1 = max(ans1, dist[i]);
	queue<int> q2;
	q2.push(e);
	while (q2.size())
	{
		int curr = q2.front(); q2.pop();
		for (pii p : invadj[curr])
		{
			int d = p.first;
			int next = p.second;
			if (dist[curr] == dist[next] + d)
			{
				if (!vst[next])
				{
					vst[next] = true;
					q2.push(next);
				}
				ans2++;
			}
		}
	}
	cout << ans1 << '\n' << ans2;
	return 0;
}