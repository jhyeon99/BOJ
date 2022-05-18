#include <bits/stdc++.h>
using namespace std;
const int MAX = 10001;
vector<int> adj[MAX], rev[MAX], scc[MAX], dfn;
bool vst[MAX];
int num[MAX];
void DFS(int v)
{
	vst[v] = true;
	for (int u : adj[v]) if (!vst[u]) DFS(u);
	dfn.push_back(v);
}
void RevDFS(int v, int number)
{
	vst[v] = true;
	num[v] = number;
	for (int u : rev[v]) if (!vst[u]) RevDFS(u, number);
}
int GetSCC(int v)
{
	memset(vst, 0, sizeof vst);
	for (int i = 1; i <= v; i++)
	{
		if (!vst[i]) DFS(i);
	}
	memset(vst, 0, sizeof vst);
	reverse(dfn.begin(), dfn.end());
	int ret = 0;
	for (int i : dfn)
	{
		if (!vst[i]) RevDFS(i, ret++);
	}
	int cnv[MAX], cnt = 0;
	for (int i = 0; i < ret; i++) cnv[i] = -1;
	for (int i = 1; i <= v; i++)
	{
		if (cnv[num[i]] == -1) cnv[num[i]] = cnt++;
		scc[cnv[num[i]]].push_back(i);
	}
	return ret;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int v, e; cin >> v >> e;
	for (int i = 0; i < e; i++)
	{
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		rev[b].push_back(a);
	}
	int ret = GetSCC(v);
	cout << ret << '\n';
	for (int i = 0; i < ret; i++)
	{
		sort(scc[i].begin(), scc[i].end());
		for (int j : scc[i]) cout << j << ' ';
		cout << -1 << '\n';
	}
	return 0;
}