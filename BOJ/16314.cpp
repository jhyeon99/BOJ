#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAX = 17;
int n, h;
vector<int> adj[100000];
bool vst[100000];
vector<int> leaf;
void DFS(int curr)
{
	for (int next : adj[curr])
	{
		if (!vst[next])
		{
			vst[next] = true;
			DFS(next);
		}
	}
	if (adj[curr].size() == 1)
	{
		leaf.push_back(curr);
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	cin >> n >> h;
	for (int i = 0; i < n - 1; i++)
	{
		int u, v; cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	vst[h] = true;
	DFS(h);
	int s = (leaf.size() + 1) / 2;
	cout << s << '\n';
	for (int i = 0; i < s; i++)
	{
		cout << leaf[i] << ' ' << leaf[leaf.size() / 2 + i] << '\n';
	}
	return 0;
}