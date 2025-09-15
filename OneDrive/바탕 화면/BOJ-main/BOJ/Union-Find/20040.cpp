#include <bits/stdc++.h>
using namespace std;
const int MAX = 500000;
int parent[MAX];
int GetParent(int idx)
{
	if (parent[idx] == idx) return idx;
	return parent[idx] = GetParent(parent[idx]);
}
void UnionParent(int a, int b)
{
	int pa = GetParent(a);
	int pb = GetParent(b);
	if (pa > pb) swap(pa, pb);
	parent[pb] = pa;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n, m; cin >> n >> m;
	for (int i = 0; i < n; i++) parent[i] = i;
	int ans = 0;
	for (int i = 0; i < m; i++)
	{
		int u, v; cin >> u >> v;
		if (GetParent(u) == GetParent(v))
		{
			ans = i + 1;
			break;
		}
		UnionParent(u, v);
	}
	cout << ans;
	return 0;
}