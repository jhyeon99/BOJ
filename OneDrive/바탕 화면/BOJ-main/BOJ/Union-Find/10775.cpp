#include <bits/stdc++.h>
using namespace std;
const int MAX = 100001;
int adj[MAX];
int UF(int idx)
{
	if (adj[idx] == idx) return idx;
	return adj[idx] = UF(adj[idx]);
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int g, p; cin >> g >> p;
	for (int i = 1; i <= g; i++) adj[i] = i;
	int ans = 0;
	for (int i = 0; i < p; i++)
	{
		int gi; cin >> gi;
		int dock = adj[gi] = UF(gi);
		if (!dock) break;
		ans++;
		adj[dock] = UF(adj[dock - 1]);
	}
	cout << ans;
	return 0;
}