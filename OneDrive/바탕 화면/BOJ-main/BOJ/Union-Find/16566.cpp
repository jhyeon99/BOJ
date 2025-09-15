#include <bits/stdc++.h>
using namespace std;
const int MAX = 4000000;
int val[MAX], par[MAX];
int Find(int x)
{
	if (par[x] == x) return x;
	return par[x] = Find(par[x]);
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n, m, k; cin >> n >> m >> k;
	for (int i = 0; i < m; i++)
	{
		cin >> val[i];
		par[i] = i;
	}
	sort(val, val + m);
	for (int i = 0; i < k; i++)
	{
		int t; cin >> t;
		int x = upper_bound(val, val + m, t) - val;
		cout << val[Find(x)] << '\n';
		par[x] = Find(x) + 1;
	}
	return 0;
}